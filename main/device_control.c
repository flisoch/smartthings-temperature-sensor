#include "device_control.h"
#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "sht3x.h"


// static temperature_state_t *temperature_state;

void change_switch_state(int switch_state)
{
	if (switch_state == SWITCH_OFF)
	{
		gpio_set_level(GPIO_OUTPUT_MAINLED, LED_OFF);
	}
	else
	{
		gpio_set_level(GPIO_OUTPUT_MAINLED, LED_ON);
	}
}

void iot_gpio_init(void)
{
	// esp sdk specific
	gpio_config_t io_conf;

	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_MAINLED;
	io_conf.pull_down_en = 1;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_VCC;
	gpio_config(&io_conf);
	io_conf.pin_bit_mask = 1 << GPIO_OUTPUT_GND;
	gpio_config(&io_conf);
	gpio_install_isr_service(0);
	gpio_set_level(GPIO_OUTPUT_MAINLED, LED_ON);
	gpio_set_level(GPIO_OUTPUT_VCC, 1);
	gpio_set_level(GPIO_OUTPUT_GND, 0);
}

void temperature_events_task(void *arg)
{
	QueueHandle_t queue = (QueueHandle_t)arg;
	sensirion_i2c_init();
			while (sht3x_probe(SHT3X_I2C_ADDR_DFLT) != STATUS_OK) {
        printf("SHT sensor probing failed\n");
    }
    printf("SHT sensor probing successful\n");

	double temperature_value = 30;
	for (;;)
	{	int32_t temperature, humidity;
		int8_t ret = sht3x_measure_blocking_read(SHT3X_I2C_ADDR_DFLT, &temperature, &humidity);
		if (ret == STATUS_OK) {
            printf("measured temperature: %0.2f degreeCelsius, "
                   "measured humidity: %0.2f percentRH\n",
                   temperature / 1000.0f, humidity / 1000.0f);
        } else {
            printf("error reading measurement: status %d\n", ret);
        }
		temperature_value = temperature_value == 30 ? 25 : 30;
		xQueueSendToBack(queue, &temperature_value, 0);
		vTaskDelay(pdMS_TO_TICKS(TEMPERATURE_EVENT_MS_RATE));
	}
}

