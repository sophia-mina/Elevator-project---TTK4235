/* This file initializes the state of the elevator:
- checks if the elevator is out of bounds, if so, move down to a valid floor
*/

#include "../header/init.h"

void init(Elevator *e){
    e->initialized = false;

    e->current_floor = elevio_floorSensor();
    if ((e->current_floor == UNDEFINED_FLOOR) && (e->dir == DIRN_STOP)) {
        e->initialized = false;
        elevio_motorDirection(DIRN_DOWN);

        while (elevio_floorSensor() == UNDEFINED_FLOOR) {
            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }
        
        elevio_motorDirection(DIRN_STOP);
        e->current_floor = elevio_floorSensor();
    } 
    
    // needs to turn OFF all the lights besides current floor light
    for (int floor = 0; floor < N_FLOORS; floor++){//
        for (int button_type = BUTTON_HALL_UP; button_type < N_BUTTONS; button_type++){
            elevio_buttonLamp(floor, button_type, OFF);
        }
    }
    
    elevio_floorIndicator(e->current_floor);
    e->dir = DIRN_STOP;
    e->state = IDLE;
    e->door_timer = 0;
    e->initialized = true;

    printf("Initialization successful. Elevator is ready.\n");

}