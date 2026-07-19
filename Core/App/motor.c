#include "main.h"
#include "cmsis_os.h"
#include "tim.h"

// 使能电机引脚
#define MOTOR_ENABLE_GPIO GPIOA
#define MOTOR_ENABLE_PIN GPIO_PIN_4
// 单/双极性引脚
#define MOTOR_BIPOLAR_GPIO GPIOB
#define MOTOR_BIPOLAR_PIN GPIO_PIN_0

void Motor_Init(void)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4500);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4500);
    HAL_GPIO_WritePin(MOTOR_BIPOLAR_GPIO, MOTOR_BIPOLAR_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO, MOTOR_ENABLE_PIN, GPIO_PIN_SET);
}

void Motor_Stop(void)
{
    HAL_GPIO_WritePin(MOTOR_ENABLE_GPIO, MOTOR_ENABLE_PIN, GPIO_PIN_RESET);
}

void Motor_Set_Vel(int16_t motor_vel)
{
    if (motor_vel > 8999)
    {
        motor_vel = 8999;
    }
    else if (motor_vel < 0)
    {
        motor_vel = 0;
    }
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, motor_vel);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, motor_vel);
}