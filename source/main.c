#include "driver/elevio.h"
#include "header/include.h"
#include <time.h>
#include "header/init.h"
#include "header/interface.h"
#include "header/states.h"

int main(){
    elevio_init();  // elevator initialization

    Elevator elevator = {0};
    elevator.queue_up = NULL;      // empty queue
    elevator.queue_down = NULL;     // empty queue
    elevator.dir = DIRN_STOP;
    elevator.prev_dir = DIRN_STOP;
    elevator.initialized = false;

    init(&elevator);    // checks if elevator is on valid floor
    int last_floor = elevator.current_floor;     // holds the current valid floor value

    
    while(1){
        elevator.current_floor = elevio_floorSensor();
        elevator.on_floor = elevio_floorSensor();
        bool stop_button = elevio_stopButton();     // defines if the stop button is pressed
        
        // holds the value of the current floor constant
        if (elevator.current_floor == UNDEFINED_FLOOR){
            elevator.current_floor = last_floor;
        } else if (elevator.current_floor != last_floor){
            last_floor = elevator.current_floor;     // updates last_floor to become the newest floor 
        }

        //updates order
        button_pressed(&elevator);
        
        fsm_update(&elevator, stop_button);


        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);//
    }

    return 0;
} 
