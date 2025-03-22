#include "motor.h"

#define NUM_MOTORS 3

motor_t motors[NUM_MOTORS] = {
    {
        .enc_a=0,
        .enc_b=1,
        .pwm=2,
        .in_1=3,
        .in_2=4,

        .kp = 1,
        .ki = 0,
        .kd = 0
    },
    {
        .enc_a=5,
        .enc_b=6,
        .pwm=7,
        .in_1=8,
        .in_2=9,

        .kp = 1,
        .ki = 0,
        .kd = 0
    },
    {
        .enc_a=10,
        .enc_b=11,
        .pwm=12,
        .in_1=13,
        .in_2=14,

        .kp = 1,
        .ki = 0,
        .kd = 0
    },
};
