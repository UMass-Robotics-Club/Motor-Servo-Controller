#include "servo.h"

#define NUM_SERVOS 3

pid_config_t pid_config = {
    .kp=1,
    .ki=0,
    .kd=0,
    .min_i=INT32_MIN,
    .max_i=INT32_MAX,
    .min_out=INT32_MIN,
    .max_out=INT32_MAX,
    .reset_err_on_cross=false
};

servo_t servos[NUM_SERVOS] = {
    {(motor_t){
        .enc_a=0,
        .enc_b=1,
        .pwm=2,
        .in_1=3,
        .in_2=4
    }, (pid_t){.config=&pid_config}},
    {(motor_t){
        .enc_a=5,
        .enc_b=6,
        .pwm=7,
        .in_1=8,
        .in_2=9
    }, (pid_t){.config=&pid_config}},
    {(motor_t){
        .enc_a=10,
        .enc_b=11,
        .pwm=12,
        .in_1=13,
        .in_2=14
    }, (pid_t){.config=&pid_config}},
};