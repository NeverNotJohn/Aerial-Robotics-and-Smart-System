#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"


// Motor pins
const int MOTOR_30 = 0;                 // pin 1  
const int MOTOR_90 = 1;                 // pin 2
const int MOTOR_150 = 2;                // pin 4 
const int MOTOR_210 = 3;                // pin 5    
const int MOTOR_270 = 4;                // pin 6
const int MOTOR_330 = 5;                // pin 7
const int LED_PIN = PICO_DEFAULT_LED_PIN;

// Input Pins
const int UPPIES = 21;

int main() {

    // Turn on lol
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    // Initialize pins
    // num = motor degrees
    // A = clockwise
    // B = counterclockwise 

    stdio_init_all();

    gpio_init(MOTOR_30);
    gpio_init(MOTOR_90);
    gpio_init(MOTOR_150);
    gpio_init(MOTOR_210);
    gpio_init(MOTOR_330);
    gpio_init(UPPIES);

    gpio_set_function(MOTOR_30, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_90, GPIO_FUNC_PWM);
    gpio_pull_down(UPPIES);

    // Tell GPIO 0 and 1 they are allocated to the PWM
    gpio_set_function(MOTOR_30, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR_90, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    int slice_num = pwm_gpio_to_slice_num(0);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 3);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 3);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);






    /*
    while (true) {
        gpio_put(MOTOR_90_A, 1);
        gpio_put(MOTOR_90_B, 0);
        if (UPPIES == 1)
        {

            gpio_put(MOTOR_90_A, 0);
            gpio_put(MOTOR_90_B, 1);
            gpio_put(MOTOR_30_A, 1);
            gpio_put(MOTOR_30_B, 0);
            gpio_put(MOTOR_90_A, 0);
            gpio_put(MOTOR_90_B, 1);
            sleep_ms(3000);
            gpio_put(MOTOR_30_A, 1);
            gpio_put(MOTOR_30_B, 1);
            gpio_put(MOTOR_90_A, 1);
            gpio_put(MOTOR_90_B, 1);
            sleep_ms(3000);
            gpio_put(MOTOR_30_A, 0);
            gpio_put(MOTOR_30_B, 0);
            gpio_put(MOTOR_90_A, 0);
            gpio_put(MOTOR_90_B, 0);
            sleep_ms(3000);
            gpio_put(MOTOR_30_A, 0);
            gpio_put(MOTOR_30_B, 1);
            gpio_put(MOTOR_90_A, 0);
            gpio_put(MOTOR_90_B, 1);
            sleep_ms(3000);
            
        }
    }

    */

   
    

    return 0;
}