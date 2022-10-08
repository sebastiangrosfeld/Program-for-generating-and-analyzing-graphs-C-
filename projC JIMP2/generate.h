#ifndef _GENERATE_H_
#define _GENERATE_H_

#include "graph.h"
#include "random.h"

typedef enum node_position
{
	MIDDLE,
	TOP_EDGE,
	BOTTOM_EDGE,
	LEFT_EDGE,
	RIGHT_EDGE,
	TOP_LEFT_CORNER,
	TOP_RIGHT_CORNER,
	BOTTOM_LEFT_CORNER,
	BOTTOM_RIGHT_CORNER
} node_position_t;

static node_position_t get_node_position(graph_t *graph, int row, int column);

static int get_node_index(graph_t *graph, int row, int column);

static void create_edge(graph_t *graph, int from, int to, random_data_t *random_data);

static void create_left_edge(graph_t *graph, int node_index, random_data_t *random_data);

static void create_right_edge(graph_t *graph, int node_index, random_data_t *random_data);

static void create_top_edge(graph_t *graph, int node_index, random_data_t *random_data);

static void create_bottom_edge(graph_t *graph, int node_index, random_data_t *random_data);

static void create_edges(graph_t *graph, int node_index, node_position_t node_position, random_data_t *random_data);

static void generate_graph(graph_t *graph, random_data_t *random_data);

static void generate_wages(graph_t *graph, random_data_t *random_data);

static void generate_consistent(graph_t *graph, random_data_t *random_data);

static void generate_random(graph_t *graph, random_data_t *random_data);

void generate(graph_t *graph, char *mode, double min_weight, double max_weight);

#endif
