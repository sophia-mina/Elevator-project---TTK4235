#pragma once

#include "include.h"
#include "queue.h"
#include "control.h"

// emergency stop button
void emerg_stop(Elevator *e);

// checks which buttons are being pressed
void button_pressed(Elevator *e);