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

static int addr = 0x68;

void GYRO_TASK()
{   
    int X_pos = 0;
    int X_spin = 0;
    int Y_pos = 0;
    int Y_spin = 0;
    int Z_pos = 0;
    int Z_spin = 0;

    //This is where the data from the gyro will be read in

    //This is where the data will be sent to the math task
    xQueueSend(XPos, &X_pos, 0);
    xQueueSend(Xspin, &X_spin, 0);
    xQueueSend(YPos, &Y_pos, 0);
    xQueueSend(Yspin, &Y_spin, 0);
    xQueueSend(ZPos, &Z_pos, 0);
    xQueueSend(Zspin, &Z_spin, 0);
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

    //This is where the power will be read in from the math task
    xQueueReceive(Motor0, &Motor0_Power, 0);
    xQueueReceive(Motor1, &Motor1_Power, 0);
    xQueueReceive(Motor2, &Motor2_Power, 0);
    xQueueReceive(Motor3, &Motor3_Power, 0);
    xQueueReceive(Motor4, &Motor4_Power, 0);
    xQueueReceive(Motor5, &Motor5_Power, 0);

    //This is where the power will be conditioned 

    //This is where the power will be sent to the motors
    pwm_set_gpio_level(0, Motor0_power_conditioned);
    pwm_set_gpio_level(1, Motor1_power_conditioned);
    pwm_set_gpio_level(2, Motor2_power_conditioned);
    pwm_set_gpio_level(3, Motor3_power_conditioned);
    pwm_set_gpio_level(4, Motor4_power_conditioned);
    pwm_set_gpio_level(5, Motor5_power_conditioned);

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