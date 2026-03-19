#pragma once
#include "include.h"


typedef struct Queue{
    int data;
    struct Queue *next;
} Queue;

// add order to the back of queue
void add_node_back(struct Queue **head, int data);

// delete order given floor (data)
void delete_node(struct Queue **head, int data);

// delete all orders in queue
void delete_queue(struct Queue **head);

// swap data of two orders
void swap_data(struct Queue *a, struct Queue *b);

// sort in increasing (up) and decreasing (down) - bUBBLE SORT, uses swap_data
void sort_up(struct Queue **head);
void sort_down(struct Queue **head);

//Bubble sort solution of queue, uses either sort up or  sort down
void sort_queue(struct Queue **head, int dir);

// checks if the queue is empty
bool queue_empty(Queue *head);

// gets the current order
int get_order(Queue *head);
