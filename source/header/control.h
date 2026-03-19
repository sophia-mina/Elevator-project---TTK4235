#pragma once
#include "include.h"
#include "queue.h"
#include "states.h"

// adds order to queue
void order_to_queue(Elevator *e, int data, int button_type);

// chooses direction of the elevator
MotorDirection choose_direction(Elevator *e);

// checks if the elevator has reached the floor of an order
bool reached_current_order(Elevator *e);