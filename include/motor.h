#ifndef __MOTOR_H
#define __MOTOR_H


#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include <math.h>


typedef enum {
    FORWARD,
    REVERSE,
    COAST,
    BREAK
} direction_e;

typedef struct {
    uint enc_a;
    uint enc_b;
    uint pwm;
    uint in_1;
    uint in_2;

    direction_e cur_dir;
    volatile int position;

    //PID variables
    float kp;
    float ki;
    float kd;

    float prevError;
    float errorIntegral;

} motor_t;

void motor_init(motor_t* motor);
void motor_set_dir(motor_t* motor, direction_e dir);
void motor_set_power(motor_t* motor, float power);
void motor_set_target(motor_t* motor, float deltaT, int target);


#endif

