#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "queue.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

QueueHandle_t XPos;
QueueHandle_t Xspin;
QueueHandle_t YPos;
QueueHandle_t Yspin;
QueueHandle_t ZPos;
QueueHandle_t Zspin;
QueueHandle_t Motor0;
QueueHandle_t Motor1;
QueueHandle_t Motor2;
QueueHandle_t Motor3;
QueueHandle_t Motor4;
QueueHandle_t Motor5;


static int addr_mpu = 0x68;
static int motor0_gpio = 0;
static int motor1_gpio = 1;
static int motor2_gpio = 2;
static int motor3_gpio = 3;
static int motor4_gpio = 4;
static int motor5_gpio = 5;





static void mpu6050_reset() {
    //Reset internal regs
    uint8_t reset[] = {0x6B, 0x80};
    i2c_write_blocking(i2c_default, addr_mpu, reset, 2, false);
    sleep_ms(200);
    
    //Wake up mpu6050 from sleep mode (caused by reset)
    uint8_t wake[] = {0x6B, 0x00};
    i2c_write_blocking(i2c_default, addr_mpu, wake, 2, false);
    sleep_ms(200);
}

static void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3]) {
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[6];

    // Start reading acceleration registers from register 0x3B for 6 bytes
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c_default, addr_mpu, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c_default, addr_mpu, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Now gyro data from reg 0x43 for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    i2c_write_blocking(i2c_default, addr_mpu, &val, 1, true);
    i2c_read_blocking(i2c_default, addr_mpu, buffer, 6, false);  // False - finished with bus

    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }
}







void GYRO_TASK()
{   
   int16_t accel[3];
   int16_t gyro[3];
   mpu6050_reset();
   while (true){
        mpu6050_read_raw(accel, gyro);
        xQueueSend(XPos, &accel[0], 0);
        xQueueSend(Xspin, &gyro[0], 0);
        xQueueSend(YPos, &accel[1], 0);
        xQueueSend(Yspin, &gyro[1], 0);
        xQueueSend(ZPos, &accel[2], 0);
        xQueueSend(Zspin, &gyro[2], 0);
   }
}

void MATH_TASK()
{   
    int X_linear_Accel = 0;
    int X_rotational_Accel = 0;
    int Y_linear_Accel = 0;
    int Y_rotational_Accel = 0;
    int Z_linear_Accel = 0;
    int Z_rotational_Accel = 0;
    int Motor0_Power = 0;
    int Motor1_Power = 0;
    int Motor2_Power = 0;
    int Motor3_Power = 0;
    int Motor4_Power = 0;
    int Motor5_Power = 0;
    while(true){
        //This is where the data from the gyro Task will be read i
        xQueueReceive(XPos, &X_linear_Accel, 0);
        xQueueReceive(Xspin, &X_rotational_Accel, 0);
        xQueueReceive(YPos, &Y_linear_Accel, 0);
        xQueueReceive(Yspin, &Y_rotational_Accel, 0);
        xQueueReceive(ZPos, &Z_linear_Accel, 0);
        xQueueReceive(Zspin, &Z_rotational_Accel, 0);
        
        //This is where the math will be done to calculate the power for each motor

        //This is where the power will be sent to the PWM task
        xQueueSend(Motor0, &Motor0_Power, 0);
        xQueueSend(Motor1, &Motor1_Power, 0);
        xQueueSend(Motor2, &Motor2_Power, 0);
        xQueueSend(Motor3, &Motor3_Power, 0);
        xQueueSend(Motor4, &Motor4_Power, 0);
        xQueueSend(Motor5, &Motor5_Power, 0);
    }
}

void PWM_TASK()
{   
    int Motor0_Power = 0;
    int Motor1_Power = 0;
    int Motor2_Power = 0;
    int Motor3_Power = 0;
    int Motor4_Power = 0;
    int Motor5_Power = 0;
    int Motor0_power_conditioned = 0;
    int Motor1_power_conditioned = 0;
    int Motor2_power_conditioned = 0;
    int Motor3_power_conditioned = 0;
    int Motor4_power_conditioned = 0;
    int Motor5_power_conditioned = 0;
    uint motor0_slice_num = pwm_gpio_to_slice_num(motor0_gpio);
    uint motor1_slice_num = pwm_gpio_to_slice_num(motor1_gpio);
    uint motor2_slice_num = pwm_gpio_to_slice_num(motor2_gpio);
    uint motor3_slice_num = pwm_gpio_to_slice_num(motor3_gpio);
    uint motor4_slice_num = pwm_gpio_to_slice_num(motor4_gpio);
    uint motor5_slice_num = pwm_gpio_to_slice_num(motor5_gpio);
    pwm_set_clkdiv(motor0_slice_num, 256.0f);
    pwm_set_clkdiv(motor1_slice_num, 256.0f);
    pwm_set_clkdiv(motor2_slice_num, 256.0f);
    pwm_set_clkdiv(motor3_slice_num, 256.0f);
    pwm_set_clkdiv(motor4_slice_num, 256.0f);
    pwm_set_clkdiv(motor5_slice_num, 256.0f);
    pwm_set_wrap(motor0_slice_num, 9804);
    pwm_set_wrap(motor1_slice_num, 9804);
    pwm_set_wrap(motor2_slice_num, 9804);
    pwm_set_wrap(motor3_slice_num, 9804);
    pwm_set_wrap(motor4_slice_num, 9804);
    pwm_set_wrap(motor5_slice_num, 9804);
    pwm_set_enabled(motor0_slice_num, true);
    pwm_set_enabled(motor1_slice_num, true);
    pwm_set_enabled(motor2_slice_num, true);
    pwm_set_enabled(motor3_slice_num, true);
    pwm_set_enabled(motor4_slice_num, true);
    pwm_set_enabled(motor5_slice_num, true);
    while(true){
    //This is where the power will be read in from the math task
        xQueueReceive(Motor0, &Motor0_Power, 0);
        xQueueReceive(Motor1, &Motor1_Power, 0);
        xQueueReceive(Motor2, &Motor2_Power, 0);
        xQueueReceive(Motor3, &Motor3_Power, 0);
        xQueueReceive(Motor4, &Motor4_Power, 0);
        xQueueReceive(Motor5, &Motor5_Power, 0);
        //This is assuming motor power is 0-1000
        Motor0_power_conditioned = (Motor0_Power*49)/100 + 490;
        Motor1_power_conditioned = (Motor1_Power*49)/100 + 490;
        Motor2_power_conditioned = (Motor2_Power*49)/100 + 490;
        Motor3_power_conditioned = (Motor3_Power*49)/100 + 490;
        Motor4_power_conditioned = (Motor4_Power*49)/100 + 490;
        Motor5_power_conditioned = (Motor5_Power*49)/100 + 490;
        //This is where the power will be sent to the motors
        pwm_set_gpio_level(0, Motor0_power_conditioned);
        pwm_set_gpio_level(1, Motor1_power_conditioned);
        pwm_set_gpio_level(2, Motor2_power_conditioned);
        pwm_set_gpio_level(3, Motor3_power_conditioned);
        pwm_set_gpio_level(4, Motor4_power_conditioned);
        pwm_set_gpio_level(5, Motor5_power_conditioned);
    }
}
int main()
{
    stdio_init_all();

    XPos = xQueueCreate(25, sizeof(int));
    Xspin = xQueueCreate(25, sizeof(int));
    YPos = xQueueCreate(25, sizeof(int));
    Yspin = xQueueCreate(25, sizeof(int));
    ZPos = xQueueCreate(25, sizeof(int));
    Zspin = xQueueCreate(25, sizeof(int));
    Motor0 = xQueueCreate(25, sizeof(int));
    Motor1 = xQueueCreate(25, sizeof(int));
    Motor2 = xQueueCreate(25, sizeof(int));
    Motor3 = xQueueCreate(25, sizeof(int));
    Motor4 = xQueueCreate(25, sizeof(int));
    Motor5 = xQueueCreate(25, sizeof(int));
    xTaskCreate(GYRO_TASK, "Accelerom", 256, NULL, 1, NULL);
    xTaskCreate(MATH_TASK, "Kinematics", 256, NULL, 2, NULL);
    xTaskCreate(PWM_TASK, "PWM", 256, NULL, 3, NULL);
    vTaskStartScheduler();

    while(1){};
}
