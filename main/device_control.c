#include "device_control.h"
#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


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
	gpio_install_isr_service(0);
	gpio_set_level(GPIO_OUTPUT_MAINLED, LED_ON);
}

void temperature_events_task(void *arg)
{
	QueueHandle_t queue = (QueueHandle_t)arg;
	// Create a 1-Wire bus, using the RMT timeslot driver

	double temperature_value = 30;
	for (;;)
	{
		temperature_value = temperature_value == 30 ? 25 : 30;
		xQueueSendToBack(queue, &temperature_value, 0);
		vTaskDelay(pdMS_TO_TICKS(TEMPERATURE_EVENT_MS_RATE));
	}
}

