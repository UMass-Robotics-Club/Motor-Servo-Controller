#include "hardware/pwm.h"

#include "motor.h"
#include "utils.h"

/**
 * Initializes a motor by configuring all GPIO and setting it to the BREAK state.
 * @param motor The motor to initialize
 */
void motor_init(motor_t* motor){
    gpio_init(motor->enc_a);
    gpio_init(motor->enc_b);
    gpio_init(motor->pwm);
    gpio_init(motor->in_1);
    gpio_init(motor->in_2);

    gpio_set_dir(motor->enc_a, GPIO_IN);
    gpio_set_dir(motor->enc_b, GPIO_IN);
    gpio_set_dir(motor->pwm, GPIO_OUT);
    gpio_set_dir(motor->enc_a, GPIO_OUT);
    gpio_set_dir(motor->enc_b, GPIO_OUT);

    gpio_set_function(motor->pwm, GPIO_FUNC_PWM);
    pwm_set_enabled(pwm_gpio_to_slice_num (motor->pwm), true);

    gpio_put(motor->in_1, 0);
    gpio_put(motor->in_2, 0);
    motor->cur_dir = BREAK;
    motor->position = 0;
}

void motor_set_dir(motor_t* motor, direction_e dir) {
    if(motor->cur_dir == dir)
        return;
    
    gpio_put(motor->in_1, dir == FORWARD || dir == COAST ? 1 : 0);
    gpio_put(motor->in_2, dir == REVERSE || dir == COAST ? 1 : 0);
    motor->cur_dir = dir;
}

void motor_set_power(motor_t* motor, uint16_t power){
    pwm_set_gpio_level(motor->pwm, power);
}

void motor_set_power_bidirectional(motor_t* motor, int32_t power){
    if(sign(power)){
        // negative
        motor_set_dir(motor, REVERSE);
        motor_set_power(motor, -power);
    } else {
        // positive
        motor_set_dir(motor, FORWARD);
        motor_set_power(motor, power);
    }
    
}