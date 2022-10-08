#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "dijkstra.h"
#include "graph.h"
#include "constants.h"

static void initialize_dijkstra_data(dijkstra_data_t *dijkstra_data, graph_t *graph, int source, int destination)
{
	dijkstra_data->source = source;
	dijkstra_data->destination = destination;

	for (int i = 0; i < graph->nodes_count; i++)
	{
		dijkstra_data->distances[i] = DBL_MAX;
		dijkstra_data->predecessors[i] = -1;
		dijkstra_data->visited[i] = BOOL_FALSE;
	}

	dijkstra_data->distances[dijkstra_data->source] = 0;
}

static dijkstra_data_t *allocate_dijkstra_data(graph_t *graph)
{
	dijkstra_data_t *dijkstra_data = malloc(sizeof *dijkstra_data);

	if (dijkstra_data == NULL)
	{
		return NULL;
	}

	dijkstra_data->distances = malloc(graph->nodes_count * sizeof dijkstra_data->distances);

	if (dijkstra_data->distances == NULL)
	{
		free(dijkstra_data);
		return NULL;
	}

	dijkstra_data->predecessors = malloc(graph->nodes_count * sizeof dijkstra_data->predecessors);

	if (dijkstra_data->predecessors == NULL)
	{
		free(dijkstra_data->distances);
		free(dijkstra_data);
		return NULL;
	}

	dijkstra_data->visited = malloc(graph->nodes_count * sizeof dijkstra_data->visited);

	if (dijkstra_data->visited == NULL)
	{
		free(dijkstra_data->predecessors);
		free(dijkstra_data->distances);
		free(dijkstra_data);
		return NULL;
	}

	return dijkstra_data;
}

static int find_min_distance_node(dijkstra_data_t *dijkstra_data, graph_t *graph)
{
	double min_distance = DBL_MAX;
	int min_distance_node = -1;

	for (int j = 0; j < graph->nodes_count; j++)
	{
		if (dijkstra_data->distances[j] < min_distance && !dijkstra_data->visited[j])
		{
			min_distance = dijkstra_data->distances[j];
			min_distance_node = j;
		}
	}

	dijkstra_data->visited[min_distance_node] = BOOL_TRUE;

	return min_distance_node;
}

static void update_distances_and_predecessors(dijkstra_data_t *dijkstra_data, graph_t *graph)
{
	int min_distance_node = find_min_distance_node(dijkstra_data, graph);

	for (int j = 0; j < graph->nodes_count; j++)
	{
		if (graph->matrix[min_distance_node][j] != NO_EDGE)
		{
			if (dijkstra_data->distances[j] > dijkstra_data->distances[min_distance_node] + graph->matrix[min_distance_node][j])
			{
				dijkstra_data->distances[j] = dijkstra_data->distances[min_distance_node] + graph->matrix[min_distance_node][j];

				dijkstra_data->predecessors[j] = min_distance_node;
			}
		}
	}
}

static void dijkstra(dijkstra_data_t *dijkstra_data, graph_t *graph)
{
	for (int i = 0; i < graph->nodes_count; i++)
	{
		update_distances_and_predecessors(dijkstra_data, graph);
	}
}

static void print_path(dijkstra_data_t *dijkstra_data, int from, int to)
{
	if (dijkstra_data->predecessors[to] == from)
	{
		printf("%d", dijkstra_data->predecessors[to]);
		printf("->%d", to);
		return;
	}

	print_path(dijkstra_data, from, dijkstra_data->predecessors[to]);

	printf("->%d", to);
}

static void print_solution(dijkstra_data_t *dijkstra_data)
{
	printf("(%d, %d) : ", dijkstra_data->source, dijkstra_data->destination);

	print_path(dijkstra_data, dijkstra_data->source, dijkstra_data->destination);

	printf("\nCost: %g\n\n", dijkstra_data->distances[dijkstra_data->destination]);
}

static void free_dijkstra_data(dijkstra_data_t *dijkstra_data)
{
	free(dijkstra_data->distances);
	free(dijkstra_data->predecessors);
	free(dijkstra_data->visited);
	free(dijkstra_data);
}

static int validate_arguments(graph_t *graph, int source, int destination)
{
	int validation_error_occured = BOOL_FALSE;

	if (source >= graph->nodes_count)
	{
		fprintf(stderr, "Source must not be greater than or equal nodes count. Received source = %d. Nodes count = %d\n", source, graph->nodes_count);
		validation_error_occured = BOOL_TRUE;
	}

	if (destination >= graph->nodes_count)
	{
		fprintf(stderr, "Destination must not be greater than or equal nodes count. Received destination = %d. Nodes count = %d\n", destination, graph->nodes_count);
		validation_error_occured = BOOL_TRUE;
	}

	return !validation_error_occured;
}

int find_path(graph_t *graph, int source, int destination)
{
	if (!validate_arguments(graph, source, destination))
	{
		return BOOL_FALSE;
	}

	dijkstra_data_t *dijkstra_data = allocate_dijkstra_data(graph);

	if (dijkstra_data == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		return BOOL_FALSE;
	}

	initialize_dijkstra_data(dijkstra_data, graph, source, destination);

	dijkstra(dijkstra_data, graph);

	print_solution(dijkstra_data);

	free_dijkstra_data(dijkstra_data);

	return BOOL_TRUE;
}
