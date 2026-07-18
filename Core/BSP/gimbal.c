#include "gimbal.h"

static Gimbal_Handle gimbal =
{
    .yaw_id = GIMBAL_YAW_ID,
    .pitch_id = GIMBAL_PITCH_ID,
    .max_vel = 3000,
    .acc = 50
};

/*初始化*/
void Gimbal_Init(void)
{
    /*使能两个电机*/
    Emm_V5_En_Control(gimbal.yaw_id, true, false);
    Emm_V5_En_Control(gimbal.pitch_id, true, false);
}

/*速度限制*/
static uint16_t Limit_Vel(int16_t vel)
{
    if(vel < 0)
        vel = -vel;
    if(vel > gimbal.max_vel)
        vel=gimbal.max_vel;
    return vel;

}

/*单轴控制*/
static void Motor_Vel_Set(uint8_t id, int16_t vel) {
    uint8_t dir;
    if (vel>=0) {
        dir=MOTOR_CW;
    }
    else {
        dir=MOTOR_CCW;
    }
    Emm_V5_Vel_Control(id, dir, Limit_Vel(vel), gimbal.acc, false);
}

/*
云台运动
yaw:水平
pitch:俯仰
*/
void Gimbal_Move(int16_t yaw_vel, int16_t pitch_vel) {
    Motor_Vel_Set(gimbal.yaw_id, yaw_vel);
    Motor_Vel_Set(gimbal.pitch_id, pitch_vel);
}

void Gimbal_Yaw(int16_t vel) {
    Motor_Vel_Set(gimbal.yaw_id, vel);
}

void Gimbal_Pitch(int16_t vel) {
    Motor_Vel_Set(gimbal.pitch_id, vel);
}

void Gimbal_Stop(void) {
    Emm_V5_Stop_Now(gimbal.yaw_id, false);
    Emm_V5_Stop_Now(gimbal.pitch_id, false);
}