#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"
#include "graph.h"
#include "constants.h"

static char *init_colors(graph_t *graph)
{
	char *colors = malloc(graph->nodes_count * sizeof *colors);

	if (colors == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		return NULL;
	}

	for (int i = 0; i < graph->nodes_count; i++)
	{
		colors[i] = WHITE;
	}

	return colors;
}

static int *init_ancestors(graph_t *graph)
{
	int *ancestors = malloc(graph->nodes_count * sizeof *ancestors);

	if (ancestors == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		return NULL;
	}

	for (int i = 0; i < graph->nodes_count; i++)
	{
		ancestors[i] = NO_ANCESTORS;
	}

	return ancestors;
}

static fifo_q_t *fifo_q_init()
{
	fifo_q_t *fifo_q = malloc(sizeof *fifo_q);

	if (fifo_q == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		return NULL;
	}

	fifo_q->q = malloc(sizeof fifo_q->q);

	if (fifo_q->q == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		return NULL;
	}

	fifo_q->size = 1; /* at the beginning size is 1 */
	fifo_q->number_of_elements = 0;

	return fifo_q;
}

static void double_q_size(fifo_q_t *fifo_q)
{
	int *nq = realloc(fifo_q->q, 2 * fifo_q->size * sizeof fifo_q->q);

	if (nq == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
	}

	fifo_q->q = nq;
	fifo_q->size *= 2;
}

static void add_to_q(fifo_q_t *fifo_q, int top)
{
	if (fifo_q->number_of_elements == fifo_q->size)
	{
		double_q_size(fifo_q);
	}

	fifo_q->q[fifo_q->number_of_elements++] = top;
}

static int pop_from_q(fifo_q_t *fifo_q)
{
	int first_in_queue = fifo_q->q[0];

	for (int i = 0; i < fifo_q->number_of_elements - 1; i++)
	{
		fifo_q->q[i] = fifo_q->q[i + 1];
	}

	fifo_q->number_of_elements = fifo_q->number_of_elements - 1;

	return first_in_queue;
}

static int not_empty_q(fifo_q_t *fifo_q)
{
	return fifo_q->number_of_elements > 0 ? BOOL_TRUE : BOOL_FALSE;
}

static void free_q(fifo_q_t *fifo_q)
{
	free(fifo_q->q);
	free(fifo_q);
}

static void add_first(fifo_q_t *fifo_q, char *colors)
{
	colors[0] = GRAY;

	add_to_q(fifo_q, 0);
}

static void add_others(fifo_q_t *fifo_q, char *colors, int *ancestors, int top, int index)
{
	colors[index] = GRAY;
	ancestors[index] = top;

	add_to_q(fifo_q, index);
}

int check_consistency(graph_t *graph)
{
	char *colors = init_colors(graph);
	int *ancestors = init_ancestors(graph);
	fifo_q_t *fifo_q = fifo_q_init();
	int top = 0;

	if (colors == NULL || ancestors == NULL || fifo_q == NULL)
	{
		return BOOL_FALSE;
	}

	add_first(fifo_q, colors);

	while (not_empty_q(fifo_q))
	{
		top = pop_from_q(fifo_q);

		for (int i = 0; i < graph->nodes_count; i++)
		{
			if (graph->matrix[top][i] != NO_EDGE && colors[i] == WHITE)
			{
				add_others(fifo_q, colors, ancestors, top, i);
			}
		}

		colors[top] = BLACK;
	}

	free_q(fifo_q);
	free(colors);

	for (int i = 1; i < graph->nodes_count; i++)
	{
		if (ancestors[i] == NO_ANCESTORS)
		{
			printf("inconsistent\n");

			free(ancestors);

			return BOOL_FALSE;
		}
	}

	printf("consistent\n");

	free(ancestors);

	return BOOL_TRUE;
}
