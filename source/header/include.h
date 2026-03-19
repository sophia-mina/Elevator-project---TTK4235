/* This file contains necessary libraries and defines common information of the elevator:
 - Constants for floors and system limits
 - ON/OFF states
 - Shared libraries used across the project*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../driver/elevio.h"

#define OFF 0
#define ON 1
#define MIN_FLOOR 0
#define MAX_FLOOR 3
#define N_FLOORS 4
#define UNDEFINED_FLOOR -1
