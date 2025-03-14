#include "hardware/irq.h"

#include "motor.h"
#include "config.h"
#include "utils.h"

void encoder_irq_handler(){
    for(int i = 0; i < NUM_SERVOS; i++){
        uint32_t a_events = gpio_get_irq_event_mask(servos[i].motor.enc_a);
        uint32_t b_events = gpio_get_irq_event_mask(servos[i].motor.enc_b);

        if (pin_change(a_events)){
            servos[i].motor.position += (a_events & GPIO_IRQ_LEVEL_HIGH) == (b_events & GPIO_IRQ_LEVEL_HIGH) ? -1 : 1;
        }
        else if(pin_change(b_events)) {
            servos[i].motor.position += (a_events & GPIO_IRQ_LEVEL_HIGH) == (b_events & GPIO_IRQ_LEVEL_HIGH) ? 1 : -1;
        }
    }
}

int main() {
    // Add shared IRQ handler to handle all encoder ticks
    irq_add_shared_handler(IO_IRQ_BANK0, encoder_irq_handler, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);

    // Initialize all servos
    for(uint8_t i = 0; i < NUM_SERVOS; i++){
        servo_init(servos+i);
    }

    // just make them all go to some value
    servo_set_target(servos, -4096);
    servo_set_target(servos+1, 4096);
    servo_set_target(servos+2, 16384);

    while(1){
        for(uint8_t i = 0; i < NUM_SERVOS; i++){
            servo_update(servos+i);
        }
    }
}