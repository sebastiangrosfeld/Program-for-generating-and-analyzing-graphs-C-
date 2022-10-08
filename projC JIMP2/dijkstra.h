#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graph.h"

typedef struct dijkstra_data
{
	double *distances;
	int *predecessors;
	int *visited;
	int source;
	int destination;
} dijkstra_data_t;

static void initialize_dijkstra_data(dijkstra_data_t *dijkstra_data, graph_t *graph, int source, int destination);

static dijkstra_data_t *allocate_dijkstra_data(graph_t *graph);

static int find_min_distance_node(dijkstra_data_t *dijkstra_data, graph_t *graph);

static void update_distances_and_predecessors(dijkstra_data_t *dijkstra_data, graph_t *graph);

static void dijkstra(dijkstra_data_t *dijkstra_data, graph_t *graph);

static void print_path(dijkstra_data_t *dijkstra_data, int from, int to);

static void print_solution(dijkstra_data_t *dijkstra_data);

static void free_dijkstra_data(dijkstra_data_t *dijkstra_data);

static int validate_arguments(graph_t *graph, int source, int destination);

int find_path(graph_t *graph, int source, int destination);

#endif
