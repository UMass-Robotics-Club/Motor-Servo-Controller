#ifndef __MOTOR_H
#define __MOTOR_H

#include "pico/stdlib.h"

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
    int32_t position;
} motor_t;

void motor_init(motor_t* motor);
void motor_set_dir(motor_t* motor, direction_e dir);
void motor_set_power(motor_t* motor, uint16_t power);
void motor_set_power_bidirectional(motor_t* motor, int32_t power);


#endif