#include <stdio.h>
#include "pico/stdlib.h"

int main() {

    // Initialize pins
    // num = motor degrees
    // A = clockwise
    // B = counterclockwise 

    stdio_init_all();

    const int MOTOR_0_A = 1;
    const int MOTOR_0_B = 2;
    const int MOTOR_45_A = 4;
    const int MOTOR_45_B = 5;
    const int MOTOR_90_A = 6;
    const int MOTOR_90_B = 7;
    const int MOTOR_135_A = 9;
    const int MOTOR_135_B = 10;
    const int MOTOR_180_A = 11;
    const int MOTOR_180_B = 12;
    const int MOTOR_225_A = 14;
    const int MOTOR_225_B = 15;
    const int MOTOR_270_A = 16;
    const int MOTOR_270_B = 17;
    const int MOTOR_315_A = 19;
    const int MOTOR_315_B = 20;

    gpio_init(MOTOR_0_A);
    gpio_init(MOTOR_0_B);
    gpio_init(MOTOR_45_A);
    gpio_init(MOTOR_45_B);
    gpio_init(MOTOR_90_A);
    gpio_init(MOTOR_90_B);
    gpio_init(MOTOR_135_A);
    gpio_init(MOTOR_135_B);
    gpio_init(MOTOR_180_A);
    gpio_init(MOTOR_180_B);
    gpio_init(MOTOR_225_A);
    gpio_init(MOTOR_225_B);
    gpio_init(MOTOR_270_A);
    gpio_init(MOTOR_270_B);
    gpio_init(MOTOR_315_A);
    gpio_init(MOTOR_315_B);

    gpio_set_dir(MOTOR_0_A, GPIO_OUT);
    gpio_set_dir(MOTOR_0_B, GPIO_OUT);
    gpio_set_dir(MOTOR_45_A, GPIO_OUT);
    gpio_set_dir(MOTOR_45_B, GPIO_OUT);
    gpio_set_dir(MOTOR_90_A, GPIO_OUT);
    gpio_set_dir(MOTOR_90_B, GPIO_OUT);
    gpio_set_dir(MOTOR_135_A, GPIO_OUT);
    gpio_set_dir(MOTOR_135_B, GPIO_OUT);
    gpio_set_dir(MOTOR_180_A, GPIO_OUT);
    gpio_set_dir(MOTOR_180_B, GPIO_OUT);
    gpio_set_dir(MOTOR_225_A, GPIO_OUT);
    gpio_set_dir(MOTOR_225_B, GPIO_OUT);
    gpio_set_dir(MOTOR_270_A, GPIO_OUT);
    gpio_set_dir(MOTOR_270_B, GPIO_OUT);
    gpio_set_dir(MOTOR_315_A, GPIO_OUT);
    gpio_set_dir(MOTOR_315_B, GPIO_OUT);
    

    while(true)
    {
        gpio_put(MOTOR_0_A, 1);
        gpio_put(MOTOR_0_B, 0);
        sleep_ms(1000);
        gpio_put(MOTOR_0_A, 0);
        gpio_put(MOTOR_0_A, 0);
        sleep_ms(1000);
    }

    return 0;
}