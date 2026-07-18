#ifndef __GIMBAL_H
#define __GIMBAL_H

#include "Emm_V5.h"
#include "stdint.h"
#include "stdbool.h"

/*云台电机定义*/
#define GIMBAL_YAW_ID     0x02
#define GIMBAL_PITCH_ID   0x01

/*电机方向定义*/
#define MOTOR_CW     0
#define MOTOR_CCW    1

typedef struct
{
    uint8_t yaw_id;
    uint8_t pitch_id;
    uint16_t max_vel; //最大速度
    uint8_t acc; //加速度
}Gimbal_Handle;

void Gimbal_Init(void);

void Gimbal_Move(int16_t yaw_vel, int16_t pitch_vel);

void Gimbal_Yaw(int16_t vel);

void Gimbal_Pitch(int16_t vel);

void Gimbal_Stop(void);

#endif