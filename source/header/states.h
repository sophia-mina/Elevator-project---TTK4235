#pragma once
#include "include.h"
#include "../header/queue.h"


// the states of the elevator
typedef enum {
    IDLE,
    MOVING,
    DOOR_OPEN,
    EMERGENCY_STOP
} ElevatorState;

// struct containing all the elevators information
typedef struct Elevator {
    ElevatorState state;
    int current_floor;
    int on_floor;
    MotorDirection dir;
    MotorDirection prev_dir;
    int door_timer;
    bool initialized;
    Queue *queue_up;
    Queue *queue_down;
    bool prev_buttons[N_FLOORS][N_BUTTONS];
} Elevator;

// state machine function
void fsm_update(Elevator *e, bool stop_button);