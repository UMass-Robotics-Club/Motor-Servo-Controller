#include "motor.h"

void motor_init(motor_t* motor){
    gpio_init(motor->enc_a);
    gpio_init(motor->enc_b);
    gpio_init(motor->pwm);
    gpio_init(motor->in_1);
    gpio_init(motor->in_2);
    

    gpio_set_dir(motor->enc_a, GPIO_IN);
    gpio_set_dir(motor->enc_b, GPIO_IN);
    gpio_set_dir(motor->pwm, GPIO_OUT);
    gpio_set_dir(motor->in_1, GPIO_OUT);
    gpio_set_dir(motor->in_2, GPIO_OUT);
    

    gpio_set_function(motor->pwm, GPIO_FUNC_PWM);
    pwm_set_enabled(pwm_gpio_to_slice_num(motor->pwm), true);

    gpio_put(motor->in_1, 0);
    gpio_put(motor->in_1, 0);
    motor->cur_dir = BREAK;
    motor->position = 0;

    motor->prevError = 0;
    motor->errorIntegral = 0;
}

void motor_set_dir(motor_t* motor, direction_e dir) {
    if(motor->cur_dir == dir)
        return;
    
    gpio_put(motor->in_1, dir == FORWARD || dir == COAST ? 1 : 0);
    gpio_put(motor->in_2, dir == REVERSE || dir == COAST ? 1 : 0);
    motor->cur_dir = dir;
}

void motor_set_power(motor_t* motor, float power){
    // Set PWM frequency (e.g., 1 kHz)
    uint slice_num = pwm_gpio_to_slice_num(motor->pwm);
    uint chan = pwm_gpio_to_channel(motor->pwm);
    pwm_set_wrap(slice_num, 12500);  // Assuming 125 MHz clock, gives 1 kHz
    pwm_set_chan_level(slice_num, chan, (uint16_t)(power * 12500.0 / 100.0));
    pwm_set_enabled(slice_num, true);
}

void motor_set_target(motor_t* motor, float deltaT, int target){
    int error = motor->position - target;
    float dedt = (error - motor->prevError)/deltaT;
    motor->errorIntegral += error*deltaT;

    float u = motor->kp * error + motor->kd * dedt + motor->ki * motor->errorIntegral;

    float power = (fabs(u) > 100.0) ? 100.0 : fabs(u);
    direction_e dir = (u > 0) ? FORWARD : REVERSE;

    motor_set_dir(motor, dir);
    motor_set_power(motor, power);
    motor->prevError = error;
}



