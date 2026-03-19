/* This file contains functions for all the buttons
- stop
- floor
 */

#include "../header/interface.h"
#include <stdbool.h>


void emerg_stop(Elevator *e){
    if (e->initialized == false) {
        return;
    }

    elevio_stopLamp(ON);

    if (e->on_floor != UNDEFINED_FLOOR) {
        elevio_doorOpenLamp(ON);
    } 
    
    elevio_motorDirection(DIRN_STOP);   // stops the elevator
    delete_queue(&e->queue_up);
    delete_queue(&e->queue_down);
}

void button_pressed(Elevator *e){
    if (!e->initialized) {
        return;
    }

    for (int floor = 0; floor < N_FLOORS; floor++){
        for (int button_type = BUTTON_HALL_UP; button_type < N_BUTTONS; button_type++){
            bool pressed = elevio_callButton(floor, button_type);

            if (pressed && !e->prev_buttons[floor][button_type]) {

                if (floor == e->current_floor &&
                    e->on_floor != UNDEFINED_FLOOR &&
                    (e->state == IDLE || e->state == DOOR_OPEN)) {
                    // 

                    elevio_motorDirection(DIRN_STOP);
                    elevio_doorOpenLamp(ON);
                    e->door_timer = 0;
                    e->state = DOOR_OPEN;
                    elevio_buttonLamp(floor, button_type, OFF);
                } else {
                    order_to_queue(e, floor, button_type);
                    elevio_buttonLamp(floor, button_type, ON);
                }
            }

            e->prev_buttons[floor][button_type] = pressed;
        }
    }
}