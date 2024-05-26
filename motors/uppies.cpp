#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Assume the potentiometer is connected to ADC channel 0
const uint POT_CHANNEL = 0;

// Assume the PWM output is on GPIO 2
const uint PWM_PIN = 2;

// Set the PWM frequency to 50Hz
const float PWM_FREQUENCY = 50.0;

int main() {
    stdio_init_all();

    // Initialize the ADC
    adc_init();
    adc_gpio_init(26 + POT_CHANNEL);
    adc_select_input(POT_CHANNEL);

    // Initialize the PWM
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);  /// Set the pin 0 to be PWM
    auto slice   = pwm_gpio_to_slice_num(PWM_PIN);
    auto channel = pwm_gpio_to_channel(PWM_PIN);

    pwm_set_clkdiv(slice, 256.0f);  /// Setting the divider to slow down the clock
    pwm_set_wrap(slice, 9804);      /// setting the Wrap time to 9764 (20 ms)
    pwm_set_enabled(slice, true);


    while (true) {
        // Read the potentiometer value
        //uint16_t pot_value = adc_read();

        // Map the potentiometer value to a PWM duty cycle
        uint16_t pwm_value = (adc_read() * 50)/417 + 490;

        // Set the PWM duty cycle
    }

    return 0;
}