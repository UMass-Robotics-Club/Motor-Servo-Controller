#ifndef __PID_H
#define __PID_H

#include "pico/stdlib.h"

typedef struct {
    float kp;
    float ki;
    float kd;
    
    // the smallest value that the integral term can contribute to the output
    int32_t min_i;
    // the largest value that the integral term can contribute to the output
    int32_t max_i;
    // the smallest value that the output can be
    int32_t min_out;
    // the largest value that the output can be
    int32_t max_out;
    // reset the total error (reset integral term) when the error crosses 0
    bool reset_err_on_cross;
} pid_config_t;

typedef struct 
{
    pid_config_t* config;

    uint64_t last_update;
    int64_t tot_err;
    int32_t last_err;
} pid_t;

void pid_reset(pid_t *pid);
int32_t pid_update(pid_t *pid, int32_t error);

#endif