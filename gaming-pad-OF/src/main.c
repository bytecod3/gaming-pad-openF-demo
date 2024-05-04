
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/adc.h"

/* pin definitions */
#define GPIO_LEFT_SWITCH    5


/* ADC channel for right */
adc_channel_t left_x_adc_channel =  ADC1_CHANNEL_6; // GPIO 34
adc_channel_t left_y_adc_channel = ADC1_CHANNEL_7; // GPIO 35
adc_channel_t right_x_adc_channel =  ADC1_CHANNEL_5; // TODO: GPIO 33
adc_channel_t right_y_adc_channel = ADC1_CHANNEL_0; // TODO: GPIO 36


/* struct to create an instance of a gaming pad */
typedef struct analog_pad {

    uint8_t switch_pin;                 // switch pin
    uint8_t x_val;                      // x-xis potentiometer analog value
    uint8_t y_val;                      // y-axis potentiometer analog value
    uint8_t sw_state;                   // state of the push button - whether presed or not
    adc_channel_t x_adc_channel;        // channel to use for x potentiometer
    adc_channel_t y_adc_channel;        // channel to use for y potentiometer

    /* returns a void - used to init an analog pad instance*/
    void (*init) (struct analog_pad* self, uint8_t switch_pin, adc1_channel_t x_adc_channel, adc_channel_t y_adc_channel); 

    /* get the analog value of the x-axis potentiometer */
    uint32_t (*get_x_val) (struct analog_pad*);        

    /* get the analog value of the y-axis potentiometer */
    uint32_t (*get_y_val) (struct analog_pad*); 

    /* check if button has been pressed */
    uint8_t (*button_pressed) (struct analog_pad*);

} AnalogPad;

/* member functions to AnalogPad struct */

 /* init an analog pad instance*/
void initPad(AnalogPad* self, uint8_t switch_pin, adc1_channel_t x_adc_channel, adc_channel_t y_adc_channel) {

    // bind pin numbers and adc channel
    self->switch_pin = switch_pin;
    self->x_adc_channel = x_adc_channel;
    self->y_adc_channel = y_adc_channel;

    // init hardware register masks
    #define GPIO_SWITCH_MASK (1 << self->switch_pin)

    // init the x-axis potentiometer
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(self->x_adc_channel, ADC_ATTEN_DB_11);

    // init the y-axis potentiometer
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(self->y_adc_channel, ADC_ATTEN_DB_11);

    // init the switch pin
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_SWITCH_MASK;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
    
    printf("HW initialization done\n");

}

/* get the analog value of the x-axis potentiometer */
uint32_t get_x_val (struct analog_pad* self) {

    uint32_t val;
    val = adc1_get_raw(self->x_adc_channel);

    return val;

}

/* get the analog value of the y-axis potentiometer */
uint32_t get_y_val (struct analog_pad* self) {

    uint32_t val;
    val = adc1_get_raw(self->y_adc_channel);

    return val;

}

/* check if button has been pressed */
uint8_t button_pressed(struct analog_pad*) {
    return 10;

}

void app_main() {

    // setup pad instances 
    // set up left pad
    AnalogPad left_pad;
    left_pad.init = initPad;
    left_pad.get_x_val = get_x_val;     
    left_pad.get_y_val = get_y_val; 
    left_pad.button_pressed = button_pressed;
    left_pad.init(&left_pad, GPIO_LEFT_SWITCH, left_x_adc_channel, left_y_adc_channel);

    // set up right pad
    AnalogPad right_pad;
    right_pad.init = initPad;
    right_pad.get_x_val = get_x_val;     
    right_pad.get_y_val = get_y_val; 
    right_pad.button_pressed = button_pressed;
    right_pad.init(&right_pad, GPIO_LEFT_SWITCH, right_x_adc_channel, right_y_adc_channel);

    // variables to hold the x and y analog values 
    uint32_t left_x_val, left_y_val, right_x_val, right_y_val;

    while(1) {

        // get the analog value of the left pad
        left_x_val = left_pad.get_x_val(&left_pad);
        left_y_val = left_pad.get_y_val(&left_pad);
        right_x_val = right_pad.get_x_val(&right_pad);
        right_y_val = right_pad.get_y_val(&right_pad);

        printf("l-x:%lu, l-y:%lu | r-x:%lu, r-y:%lu \n", 
            (unsigned long) left_x_val, 
            (unsigned long) left_y_val, 
            (unsigned long) right_x_val, 
            (unsigned long) right_y_val
            );
        vTaskDelay(5 / portTICK_PERIOD_MS); // minimal task delay to prevent watchdog timer from triggering
    }
    
}