/* This file contains all the logic for the elevator:
- adding orders to the correct queue
- getting an order from the queue
- choosing motor direction
- checks if the elevator has reached the floor of the current order
*/

#include "../header/control.h"

void order_to_queue(Elevator *e, int data, int button_type){
    if(button_type == BUTTON_HALL_UP){
        if (data == MIN_FLOOR) {
            add_node_back(&e->queue_down, data);
            sort_down(&e->queue_down);
            return;
        }
        add_node_back(&e->queue_up, data);
        sort_up(&e->queue_up);

    } else if(button_type == BUTTON_HALL_DOWN){
        if (data == MAX_FLOOR) {
            add_node_back(&e->queue_up, data);
            sort_up(&e->queue_up);
            return;
        }
        add_node_back(&e->queue_down, data);
        sort_down(&e->queue_down);

    } else { // BUTTON_CAB
        if(data == e->current_floor){
            add_node_back(&e->queue_up, data);
            add_node_back(&e->queue_down, data);
        }else if(data > e->current_floor){
            add_node_back(&e->queue_up, data);
            sort_up(&e->queue_up);
        } else {
            add_node_back(&e->queue_down, data);
            sort_down(&e->queue_down);
        }
    }
}



MotorDirection choose_direction(Elevator *e){
    if(e->on_floor == UNDEFINED_FLOOR && e->dir == DIRN_STOP){
        if(!queue_empty(e->queue_up) && get_order(e->queue_up)==e->current_floor){
            return -e->prev_dir;
        }
        if(!queue_empty(e->queue_down) && get_order(e->queue_down)==e->current_floor){
            return -e->prev_dir;
        }
    }

    if ((e->current_floor == MIN_FLOOR) && ((!queue_empty(e->queue_up)) || (!queue_empty(e->queue_down)))) {
        return DIRN_UP;
    }

    if ((e->current_floor == MAX_FLOOR) && ((!queue_empty(e->queue_up)) || (!queue_empty(e->queue_down)))) {
        return DIRN_DOWN;
    }

    if (e->dir == DIRN_UP) {
        if (!queue_empty(e->queue_up)) {
            if (e->current_floor < get_order(e->queue_up)){
                return DIRN_UP;
            }
            return DIRN_DOWN;
        } else if (!queue_empty(e->queue_down)) {
            if (e->current_floor > get_order(e->queue_down)){
                return DIRN_DOWN;
            }
            return DIRN_UP;
        }
    } 

    if (e->dir == DIRN_DOWN) {
        if (!queue_empty(e->queue_down)){
            if (e->current_floor > get_order(e->queue_down)){
                return DIRN_DOWN;
            }
            return DIRN_UP;
        } else if (!queue_empty(e->queue_up)){
            if (e->current_floor < get_order(e->queue_up)){
                return DIRN_UP;
            }
            return DIRN_DOWN;
        } 
    }

    if (!queue_empty(e->queue_up)) {
        return DIRN_UP;
    }

    if (!queue_empty(e->queue_down)) {
        return DIRN_DOWN;
    }

    return DIRN_STOP;
}


bool reached_current_order(Elevator *e){
    if (e->on_floor == UNDEFINED_FLOOR) {
        return false;
    }

    if (e->dir == DIRN_UP) {
        if (!queue_empty(e->queue_up) &&
            e->on_floor == get_order(e->queue_up)) {
            return true;
        }

        if (queue_empty(e->queue_up) &&
            !queue_empty(e->queue_down) &&
            e->on_floor == get_order(e->queue_down)) {
            get_order(e->queue_up);
            return true;
        }
    }

    if (e->dir == DIRN_DOWN) {
        if (!queue_empty(e->queue_down) &&
            e->on_floor == get_order(e->queue_down)) {
            get_order(e->queue_down);
            return true;
        }

        if (queue_empty(e->queue_down) &&
            !queue_empty(e->queue_up) &&
            e->on_floor == get_order(e->queue_up)) {
            get_order(e->queue_up);
            return true;
        }
    }

    return false;
}