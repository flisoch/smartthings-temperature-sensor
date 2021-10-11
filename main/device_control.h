#include "driver/ledc.h"


#define GPIO_OUTPUT_MAINLED 2
#define GPIO_INPUT_SWITCH 27
#define GPIO_OUTPUT_BUZZER 12
#define GPIO_OUTPUT_RGBLED_B 32
#define GPIO_TEMPERATURE_SENSOR 13

#define LEDC_RED_GPIO (26)
#define LEDC_RED_CHANNEL LEDC_CHANNEL_0
#define LEDC_GREEN_GPIO (25)
#define LEDC_GREEN_CHANNEL LEDC_CHANNEL_1
#define LEDC_BLUE_GPIO (32)
#define LEDC_BLUE_CHANNEL LEDC_CHANNEL_2
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_HS_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_MIN_DUTY (0)
#define LEDC_MAX_DUTY (4096)
#define LEDC_FADE_TIME (1000)

#define TEMPERATURE_EVENT_MS_RATE 1000
#define BUZZER_SOUND_DURATION 3000
#define RGB_BOILING_ADJUSTMENT_DURATION 20
#define BUTTON_DEBOUNCE_TIME_MS 20
#define HEATING_SETPOINT_RGB_DURATION 1500

enum switch_onoff_state
{
    SWITCH_OFF = 1,
    SWITCH_ON = 0,
};

enum led_gpio_state
{
    LED_ON = 1,
    LED_OFF = 0,
};

void change_switch_state(int switch_state);
void iot_gpio_init(void);
void temperature_events_task(void *arg);