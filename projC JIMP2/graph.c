#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "constants.h"

static int handle_row_allocation_error(graph_t *graph, int row_index)
{
	fprintf(stderr, ALLOCATION_ERROR);

	while (--row_index >= 0)
	{
		free(graph->matrix[row_index]);
	}

	free(graph->matrix);
	free(graph);

	return BOOL_FALSE;
}

static void initialize_matrix(graph_t *graph)
{
	for (int i = 0; i < graph->nodes_count; i++)
	{
		for (int j = 0; j < graph->nodes_count; j++)
		{
			graph->matrix[i][j] = NO_EDGE;
		}
	}
}

static int allocate_matrix_rows(graph_t *graph)
{
	for (int i = 0; i < graph->nodes_count; i++)
	{
		graph->matrix[i] = malloc(graph->nodes_count * sizeof graph->matrix[i]);

		if (graph->matrix[i] == NULL)
		{
			return handle_row_allocation_error(graph, i);
		}
	}

	initialize_matrix(graph);

	return BOOL_TRUE;
}

static int allocate_graph_matrix(graph_t *graph)
{
	graph->matrix = malloc(graph->nodes_count * sizeof graph->matrix);

	if (graph->matrix == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		free(graph);
		return BOOL_FALSE;
	}

	return allocate_matrix_rows(graph);
}

graph_t *initialize(int rows, int columns)
{
	graph_t *graph = malloc(sizeof *graph);

	if (graph == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		return NULL;
	}

	graph->rows = rows;
	graph->columns = columns;
	graph->nodes_count = rows * columns;

	if (!allocate_graph_matrix(graph))
	{
		return NULL;
	}

	return graph;
}

void free_graph(graph_t *graph)
{
	for (int i = 0; i < graph->nodes_count; i++)
	{
		free(graph->matrix[i]);
	}

	free(graph->matrix);
	free(graph);
}

#ifdef DEBUG

void print_graph(graph_t *graph)
{
	printf("Liczba wierszy: %d\n", graph->rows);
	printf("Liczba kolumn: %d\n", graph->columns);
	printf("Liczba wierzcholkow: %d\n", graph->nodes_count);

	for (int i = 0; i < graph->nodes_count; i++)
	{
		for (int j = 0; j < graph->nodes_count; j++)
		{
			printf("%g ", graph->matrix[i][j]);
		}

		printf("\n");
	}
}

#endif
