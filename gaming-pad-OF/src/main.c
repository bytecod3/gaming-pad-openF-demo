
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

/* pin definitions */
#define GPIO_LEFT_PAD_X   2
#define GPIO_RIGHT_PAD_Y  4

typedef struct analog_pad {
    uint8_t x_pin;              // x-axis pin
    uint8_t y_pin;              // y-axis pin
    uint8_t x_val;              // x-xis potentiometer analog value
    uint8_t y_val;              // y-axis potentiometer analog value
    uint8_t sw_state;           // state of the push button - whether presed or not

    void (*init) (AnalogPad* self, uint8_t X_GPIO_PIN, uint8_t Y_GPIO_PIN); // returns a void - used to init an analog pad instance

} AnalogPad;

/* member functions to AnalogPad struct */
void initPad(AnalogPad* self, uint8_t X_GPIO_PIN, uint8_t Y_GPIO_PIN) {

    // bind pin numbers
    self->x_pin = X_GPIO_PIN;
    self->y_pin = Y_GPIO_PIN;

    // init hardware register masks
    #define GPIO_LEFT_PAD_MASK (1 << self->x_pin)
    #define GPIO_RIGHT_PAD_MASK (1 << self->y_pin)

    // init the X potentiometer pin
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_LEFT_PAD_MASK;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    // init the X potentiometer pin
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_LEFT_PAD_MASK;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

}


void app_main() {

    // set up gpio 
    gpio_config_t io_conf;

    // setup pad instances -  left and right 
    AnalogPad left_pad;
    left_pad.init = initPad;       
    left_pad.init(&left_pad, GPIO_LEFT_PAD_X, GPIO_RIGHT_PAD_Y);

    while(1) {
        printf("%d\n", 56);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}