#include "driver/gpio.h"

#define LED 2
#define button 15
#define mask_out (1 << LED)
#define mask_in (15<<button)

static void IRAM_ATTR InterruptFunction(void* args){
    gpio_set_level(LED,0);
}


void app_main(){

gpio_config_t GPIOconfig;

GPIOconfig.mode = GPIO_MODE_OUTPUT;
GPIOconfig.intr_type = 0;
GPIOconfig.pull_down_en = 0;
GPIOconfig.pull_up_en = 0;
GPIOconfig.pin_bit_mask = mask_out;

gpio_config(&GPIOconfig);

gpio_set_level(LED,1);

GPIOconfig.mode = GPIO_MODE_INPUT;
GPIOconfig.intr_type = GPIO_INTR_POSEDGE;
GPIOconfig.pull_down_en = 0;
GPIOconfig.pull_up_en = 0;
GPIOconfig.pin_bit_mask = mask_in;

gpio_config(&GPIOconfig);

gpio_install_isr_service(0);
gpio_isr_handler_add(button,InterruptFunction,(void*) button);



}