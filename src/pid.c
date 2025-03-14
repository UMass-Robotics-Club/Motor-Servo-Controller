#include "pid.h"
#include "utils.h"

void pid_reset(pid_t *pid){
    pid->last_err = 0;
    pid->tot_err = 0;
    pid->last_update = time_us_64();
}

int32_t pid_update(pid_t *pid, int32_t err){
    // get change in time
    uint64_t time = time_us_64();
    uint32_t dt = time - pid->last_update;
    pid->last_update = time;
    
    // get rate of error change
    float de_dt = (err - pid->last_err) / (float) dt;

    // reset total error
    if(pid->config->reset_err_on_cross && sign(err) != sign(pid->last_err))
        pid->tot_err=0;
    
    // update other stuff
    pid->tot_err+=err*dt;
    pid->last_err = err;
    
    // calculate output
    int32_t i = range((int32_t)(pid->config->ki*pid->tot_err), pid->config->min_i, pid->config->max_i);

    return range((int32_t)(pid->config->kp*err + pid->config->kd*de_dt) + i, pid->config->min_out, pid->config->max_out);
}