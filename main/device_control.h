
#define GPIO_OUTPUT_MAINLED 2
#define GPIO_SDA 4
#define GPIO_SCL 5
#define GPIO_OUTPUT_VCC 12
#define GPIO_OUTPUT_GND 13


#define TEMPERATURE_EVENT_MS_RATE 3000
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