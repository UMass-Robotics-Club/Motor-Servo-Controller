#include <stdio.h>
#include "pico/stdlib.h"
#include "motor.h"
#include "config.h"

uint32_t prevTime = 0;

void readEncoder(uint gpio, uint32_t events){
    motor_t* motor = NULL;
    int m = 0;
    for(int i = 0; i < NUM_MOTORS; i++){
        if(gpio == motors[i].enc_a && (events & GPIO_IRQ_EDGE_RISE)){
            m = i;
            motor = &motors[i];
            break;
        }
    }

    if(motor == NULL) return;

    int b = gpio_get(motor->enc_b);
    if(b > 0)
        motor->position++;
    else
        motor->position--; 
}


int main() {
    stdio_init_all();

    for(int i = 0; i < NUM_MOTORS; i++){
        motor_init(&motors[i]);
    }

    for(int i = 0; i < NUM_MOTORS; i++){
        gpio_set_irq_enabled_with_callback(motors[i].enc_a, GPIO_IRQ_EDGE_RISE, true, &readEncoder);
    }
    

    while(1) {
        // test code to make both motors move in a sinusoid

        int target1 = 500*sin(prevTime/1e6);
        int target2 = 250*cos(prevTime/1e6);
        uint32_t currTime = time_us_32();
        float deltaT = ((float)(currTime - prevTime))/1.0e6; 
        prevTime = currTime;
        motor_set_target(&motors[0], deltaT, target1);
        motor_set_target(&motors[1], deltaT, target2);
    }
}
