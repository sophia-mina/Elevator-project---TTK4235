/* This file handels all functions related to the queue:
- adding orders to the queue
- removing orders from the queue
- removing/emptying queues
- swapes the place between two orders in the queue
- sort the queue in ascending and descending order
- sorting the queue
- checks if the queue is empty
- gets the current order
 */

#include "../header/queue.h"

void add_node_back(struct Queue **head, int data){
    struct Queue *new_order = malloc(sizeof(struct Queue));
    if (new_order == NULL){
        return;
    }

    new_order->data = data;
    new_order->next = NULL;

    if(*head == NULL){
        *head = new_order;
        return;
    }

    struct Queue *current = *head;
    while(current != NULL){
        if(current->data == data){
            free(new_order);
            return;
        }
        current = current->next;
    }

    struct Queue *last_order = *head;
    while(last_order->next != NULL){
        last_order = last_order->next;
    }
    last_order->next = new_order;
}

void delete_node(struct Queue **head, int data){
    // checks if the queue is already empty
    if (*head == NULL){
        return;
    }

    struct Queue *temp;

    // delete head and turn OFF the light
    if((*head)->data == data){
        for (int button_type = BUTTON_HALL_UP; button_type < N_BUTTONS; button_type++) {
            elevio_buttonLamp(data, button_type, OFF);
        }

        temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    // iterate through queue
    struct Queue *current = *head;

    while(current->next != NULL){
        if(current->next->data == data){
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

void delete_queue(struct Queue **head){
    if (*head == NULL){
        return;
    }
    struct Queue *current = *head;  
    struct Queue *next;
    // Iterate through queue and delete all nodes
    while(current != NULL){
            next = current->next;   // save next nodes adress
            free(current);          // free current node
            current = next;         // next node
    }
    *head = NULL;
}


void swap_data(struct Queue *a, struct Queue *b){
    int temp = a->data;
    a-> data = b->data;
    b->data = temp;
}

void sort_up(struct Queue **head){
    int swapped;
    struct Queue *ptr1;
    struct Queue *lptr = NULL;

    // Check if queue empty or only has one order
    if(*head == NULL || (*head)->next == NULL){
        return;
    }

    // Sort until there is nothing to swap, aka correct order
    do{
        swapped = 0;
        ptr1 = *head;

        while(ptr1->next != lptr){                  // current order that is checked is not previous
            if(ptr1->data > ptr1->next->data){      // swap if next order has lower value
                swap_data(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while(swapped);
}

void sort_down(struct Queue **head){
    int swapped;
    struct Queue *ptr1;
    struct Queue *lptr = NULL;

    // Check if queue empty or only has one order
    if(*head == NULL || (*head)->next == NULL){
        return;
    }

    do{
        swapped = 0;
        ptr1 = *head;

        while(ptr1->next != lptr){
            if(ptr1->data < ptr1->next->data){    // swap if next order has higher value
                swap_data(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while(swapped);
}

void sort_queue(struct Queue **head, int dir){
    if(dir == DIRN_UP){
        sort_up(head);
    }else{
        sort_down(head);
    }
}

bool queue_empty(Queue *head){
    return head == NULL;
}

int get_order(Queue *head){
    if(head == NULL){
        return 0;
    }
    return head->data;
}