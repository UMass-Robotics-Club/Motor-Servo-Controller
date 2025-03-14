#include "motor.h"
#include "pid.h"

typedef struct{
    motor_t motor;
    pid_t pid;

    int32_t target;
} servo_t;

void servo_init(servo_t* servo);
void servo_set_target(servo_t *servo, int32_t target);
void servo_update(servo_t *servo);