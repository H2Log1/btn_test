#include "cmsis_os.h"
#include "main.h"
#include "Emm_V5.h"
#include "stdbool.h"

typedef struct MOTOR{
    uint8_t addr;
    uint8_t dir[2]; //正转，反转
    double vel;
    double acc;
    double round;
    bool snF;
    bool svF;
} MOTOR;

MOTOR motor[2] = {
    // {0x01, {0x01, 0x00}, 2000.0, 200.0, 1, true, true}, 
    // {0x02, {0x00, 0x01}, 2000.0, 200.0, 1, true, true} 
    // {0x01, {0x01, 0x00}, 2000.0, 200.0, 0.05, false, true}, 
    // {0x02, {0x00, 0x01}, 2000.0, 200.0, 1.0, false, true} 
    {0x01, {0x01, 0x00}, 30.0, 10.0, 0.05, false, true}, 
    {0x02, {0x00, 0x01}, 30.0, 10.0, 1.0, false, true}  
};

// 步进电机控制函数
void Step_Motor_Set_Speed(float x_rpm, float y_rpm)
{
    uint8_t x_dir, y_dir;
    uint16_t x_speed_scaled, y_speed_scaled;

    x_dir = (x_rpm >= 0) ? motor[1].dir[0] : motor[1].dir[1];
    y_dir = (y_rpm >= 0) ? motor[0].dir[0] : motor[0].dir[1];
    
    // 速度换算（0.1RPM单位）
    x_speed_scaled = (uint16_t)(ABS(x_rpm) * 10 + 0.5f);
    y_speed_scaled = (uint16_t)(ABS(y_rpm) * 10 + 0.5f);
    
    // X轴电机控制
    Emm_V5_Vel_Control(motor[1].addr, x_dir, x_speed_scaled, motor[1].acc, motor[1].snF);
    osDelay(10);
    
    // Y轴电机控制
    Emm_V5_Vel_Control(motor[0].addr, y_dir, y_speed_scaled, motor[0].acc, motor[0].snF);
    osDelay(10);
}

// 角度旋转控制
void Step_Motor_Rotate_X_Angle(int16_t angle)
{
    uint8_t dir;
    uint32_t pulses;
    
    // 角度限制
    if(angle > 180) angle = 180;
    if(angle < -180) angle = -180;
    
    // 方向判断：CW（右转）为1，CCW（左转）为0
    if(angle >= 0)
    {
        dir = 1; // CW
        pulses = (uint32_t)(angle * 150); // 角度转脉冲数
    }
    else
    {
        dir = 0; // CCW
        pulses = (uint32_t)((-angle) * 150);
    }
    
    // 发送位置控制命令
    Emm_V5_Pos_Control(motor[1].addr, dir,
                       motor[1].vel, motor[1].acc, pulses, 
                       false, motor[1].snF);
}



void StartMotorTask(void *argument){
    Emm_V5_En_Control(motor[0].addr, true, motor[0].snF);
    osDelay(10);
    Emm_V5_En_Control(motor[1].addr, true, motor[1].snF);
    osDelay(10);

    // Emm_V5_Origin_Set_O(motor[0].addr, motor[0].svF);
    // osDelay(10);
    // Emm_V5_Origin_Set_O(motor[1].addr, motor[1].svF);
    // osDelay(10);

    for(;;){
        osMessageQueueGet(BtnQueueHandle, &click, 0, osWaitForever);
        if (click == 1) {
            // Emm_V5_Pos_Control(motor[0].addr, motor[0].dir[0], motor[0].vel, motor[0].acc, 3200*motor[0].round, 0x00, motor[0].snF);
            // osDelay(10);
            // Emm_V5_Pos_Control(motor[1].addr, motor[1].dir[1], motor[1].vel, motor[1].acc, 3200*motor[1].round, 0x00, motor[1].snF);
            // osDelay(10);
            // Emm_V5_Synchronous_motion(0x00);

            // Emm_V5_Pos_Control(motor[0].addr, motor[0].dir[0], motor[0].vel, motor[0].acc, 3200*motor[0].round, 0x00, motor[0].snF);
            // osDelay(1000);
            // Emm_V5_Pos_Control(motor[1].addr, motor[1].dir[1], motor[1].vel, motor[1].acc, 3200*motor[1].round, 0x00, motor[1].snF);
            // osDelay(1000);
            // Emm_V5_Pos_Control(motor[0].addr, motor[0].dir[1], motor[0].vel, motor[0].acc, 3200*motor[0].round, 0x00, motor[0].snF);
            // osDelay(1000);
            // Emm_V5_Pos_Control(motor[1].addr, motor[1].dir[0], motor[1].vel, motor[1].acc, 3200*motor[1].round, 0x00, motor[1].snF);
            // osDelay(1000);

            // Emm_V5_Synchronous_motion(0x00);

            Emm_V5_Vel_Control(motor[1].addr, motor[1].dir[0], motor[1].vel, motor[1].acc, motor[1].snF);

            osDelay(1000);

            Emm_V5_Stop_Now(motor[1].addr, motor[1].snF);

            osDelay(10);



        }
        else if(click == 2)
        {
            // Emm_V5_Pos_Control(motor[0].addr, motor[0].dir[1], motor[0].vel, motor[0].acc, 3200*motor[0].round, 0x00, motor[0].snF); 
            // osDelay(10);
            // Emm_V5_Pos_Control(motor[1].addr, motor[1].dir[0], motor[1].vel, motor[1].acc, 3200*motor[1].round, 0x00, motor[1].snF); 
            // osDelay(10);
            // Emm_V5_Synchronous_motion(0x00);

            // Emm_V5_Origin_Trigger_Return(motor[0].addr, 0x00, motor[0].snF);
            // osDelay(10);
            // Emm_V5_Origin_Trigger_Return(motor[1].addr, 0x00, motor[1].snF);
            // osDelay(10);
            // Emm_V5_Synchronous_motion(0x00);

            osDelay(10);
        }
    }
}