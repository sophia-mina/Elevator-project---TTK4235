/* This files contains the elevators state machine */
#include "../header/states.h"
#include "../header/control.h"
#include "../header/interface.h"


void fsm_update(Elevator *e, bool stop_button){
    // initializes the elevator
    if (e->initialized && stop_button) {
        e->state = EMERGENCY_STOP;
    }
    
    switch(e->state){

            case IDLE:

                elevio_floorIndicator(e->current_floor); 

                if (!queue_empty(e->queue_up) || !queue_empty(e->queue_down)) {
                    e->dir = choose_direction(e);
                    elevio_motorDirection(e->dir);
                    e->state = MOVING;
                } else {
                    e->dir = DIRN_STOP;
                    elevio_motorDirection(e->dir);
                }
                break;

            case MOVING:

                elevio_floorIndicator(e->current_floor); 

                if (reached_current_order(e)){
            
                    // removes reached order, sets on lights, stops motor, starts timer and door opens
                    delete_node(&e->queue_up, e->current_floor);
                    delete_node(&e->queue_down, e->current_floor);
                    elevio_motorDirection(DIRN_STOP);
                    elevio_doorOpenLamp(ON);
                    e->door_timer = 0;  // starts timer
                    e->state = DOOR_OPEN;
                } 
                break;

            case DOOR_OPEN:

                // checks if there is an obstruction
                if (elevio_obstruction()) {
                    e->door_timer = 0;
                } else {
                    e->door_timer++;
                }

                // when the door has been open for 3 seconds
                if(e->door_timer >= 150){
                    elevio_doorOpenLamp(OFF);

                    if (!queue_empty(e->queue_up) || !queue_empty(e->queue_down)) {
                        e->dir = choose_direction(e);
                        elevio_motorDirection(e->dir);
                        e->state = MOVING;
                    } else {
                        e->state = IDLE;
                    }
                }

                break;

            case EMERGENCY_STOP:
            
                e->prev_dir = e->dir;
                elevio_motorDirection(DIRN_STOP);
                elevio_stopLamp(ON);
                emerg_stop(e);

                if (!stop_button) {
                    elevio_stopLamp(OFF);
                    if (e->on_floor != UNDEFINED_FLOOR) {
                        e->door_timer = 0;
                        e->state = DOOR_OPEN;
                    } else {
                        //init(e);
                        for (int floor = 0; floor < N_FLOORS; floor++){//
                            for (int button_type = BUTTON_HALL_UP; button_type < N_BUTTONS; button_type++){
                                elevio_buttonLamp(floor, button_type, OFF);
                            }
                        }
                        e->state = IDLE;
                    }
                }
                break;
        }
}