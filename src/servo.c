#include "servo.h"

void servo_init(servo_t* servo){
    motor_init(&servo->motor);
    pid_reset(&servo->pid);
    servo->target = 0;
}

void servo_set_target(servo_t *servo, int32_t target){
    servo->target = target;
}

void servo_update(servo_t *servo){
    motor_set_power_bidirectional(&servo->motor, pid_update(&servo->pid, servo->target-servo->motor.position));
}