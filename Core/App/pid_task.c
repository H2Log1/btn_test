#include "cmsis_os.h"
#include "main.h"
#include "pid.h"
#include "motor.h"

volatile double target_vel = 100.0;

float pwm = 0.0f;
float speed = 0.0f;
Pid_t pid_motor = {0};

void StartPIDTask(void *argument)
{


    // PidInit(
    //     &pid_motor,
    //     POSITION_PID,
    //     4500,  // 最大PWM
    //     3000,  // 积分限幅
    //     2.0f,  // 死区
    //     15.0f, // Kp
    //     20.0f, // Ki
    //     5.0f   // Kd
    // );

    PidInit(
        &pid_motor,
        POSITION_PID,
        4500,     // PWM基准
        3000,     // 积分限幅
        2.0f,     // 死区
        PID_K[0], // Kp
        PID_K[1], // Ki
        PID_K[2]  // Kd
    );

    for (;;)
    {
        pid_motor.p = PID_K[0];
        pid_motor.i = PID_K[1];
        pid_motor.d = PID_K[2];

        // 当前速度
        speed = now_vel;

        // PID
        float pid_out = PidCalc(&pid_motor, speed, target_vel);

        pwm = 4500.0f + pid_out; // 基准PWM为4500

        // pwm += pid_out;

        Motor_Set_Vel((uint16_t)pwm);

        osDelay(10);
    }
}