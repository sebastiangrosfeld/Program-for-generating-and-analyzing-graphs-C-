#ifndef _BFS_H_
#define _BFS_H_

#include "graph.h"

typedef struct fifo_q
{
	int *q;					/* the queue */
	int number_of_elements; /* actual number of elements */
	int size;				/* the queue size */
} fifo_q_t;

static char *init_colors(graph_t *graph);

static int *init_ancestors(graph_t *graph);

static fifo_q_t *fifo_q_init();

static void double_q_size(fifo_q_t *fifo_q);

static void add_to_q(fifo_q_t *fifo_q, int top);

static int pop_from_q(fifo_q_t *fifo_q);

static int not_empty_q(fifo_q_t *fifo_q);

static void free_q(fifo_q_t *fifo_q);

static void add_first(fifo_q_t *fifo_q, char *colors);

static void add_others(fifo_q_t *fifo_q, char *colors, int *ancestors, int top, int index);

int check_consistency(graph_t *graph);

#endif
