#include <stdlib.h>
#include <string.h>
#include "generate.h"
#include "graph.h"
#include "random.h"
#include "constants.h"
#include "bfs.h"

static node_position_t get_node_position(graph_t *graph, int row, int column)
{
	if (row == 1 && column == 1)
	{
		return TOP_LEFT_CORNER;
	}
	else if (row == 1 && column == graph->columns)
	{
		return TOP_RIGHT_CORNER;
	}
	else if (row == graph->rows && column == 1)
	{
		return BOTTOM_LEFT_CORNER;
	}
	else if (row == graph->rows && column == graph->columns)
	{
		return BOTTOM_RIGHT_CORNER;
	}
	else if (row == 1)
	{
		return TOP_EDGE;
	}
	else if (row == graph->rows)
	{
		return BOTTOM_EDGE;
	}
	else if (column == 1)
	{
		return LEFT_EDGE;
	}
	else if (column == graph->columns)
	{
		return RIGHT_EDGE;
	}
	else
	{
		return MIDDLE;
	}
}

static int get_node_index(graph_t *graph, int row, int column)
{
	return ((row - 1) * graph->columns) + (column - 1);
}

static void create_edge(graph_t *graph, int from, int to, random_data_t *random_data)
{
	int edge_exists = BOOL_TRUE;

	if (random_data->random_edges)
	{
		edge_exists = random_edge();
	}

	graph->matrix[from][to] = edge_exists ? random_weight(random_data) : NO_EDGE;
}

static void create_left_edge(graph_t *graph, int node_index, random_data_t *random_data)
{
	create_edge(graph, node_index, node_index - 1, random_data);
}

static void create_right_edge(graph_t *graph, int node_index, random_data_t *random_data)
{
	create_edge(graph, node_index, node_index + 1, random_data);
}

static void create_top_edge(graph_t *graph, int node_index, random_data_t *random_data)
{
	create_edge(graph, node_index, node_index - graph->columns, random_data);
}

static void create_bottom_edge(graph_t *graph, int node_index, random_data_t *random_data)
{
	create_edge(graph, node_index, node_index + graph->columns, random_data);
}

static void create_edges(graph_t *graph, int node_index, node_position_t node_position, random_data_t *random_data)
{
	switch (node_position)
	{
	case TOP_LEFT_CORNER:
		create_right_edge(graph, node_index, random_data);
		create_bottom_edge(graph, node_index, random_data);
		break;
	case TOP_RIGHT_CORNER:
		create_left_edge(graph, node_index, random_data);
		create_bottom_edge(graph, node_index, random_data);
		break;
	case BOTTOM_LEFT_CORNER:
		create_right_edge(graph, node_index, random_data);
		create_top_edge(graph, node_index, random_data);
		break;
	case BOTTOM_RIGHT_CORNER:
		create_left_edge(graph, node_index, random_data);
		create_top_edge(graph, node_index, random_data);
		break;
	case TOP_EDGE:
		create_left_edge(graph, node_index, random_data);
		create_right_edge(graph, node_index, random_data);
		create_bottom_edge(graph, node_index, random_data);
		break;
	case BOTTOM_EDGE:
		create_left_edge(graph, node_index, random_data);
		create_right_edge(graph, node_index, random_data);
		create_top_edge(graph, node_index, random_data);
		break;
	case LEFT_EDGE:
		create_right_edge(graph, node_index, random_data);
		create_top_edge(graph, node_index, random_data);
		create_bottom_edge(graph, node_index, random_data);
		break;
	case RIGHT_EDGE:
		create_left_edge(graph, node_index, random_data);
		create_top_edge(graph, node_index, random_data);
		create_bottom_edge(graph, node_index, random_data);
		break;
	case MIDDLE:
		create_left_edge(graph, node_index, random_data);
		create_right_edge(graph, node_index, random_data);
		create_top_edge(graph, node_index, random_data);
		create_bottom_edge(graph, node_index, random_data);
		break;
	default:
		break;
	}
}

static void generate_graph(graph_t *graph, random_data_t *random_data)
{
	for (int row = 1; row <= graph->rows; row++)
	{
		for (int column = 1; column <= graph->columns; column++)
		{
			int node_index = get_node_index(graph, row, column);
			node_position_t node_position = get_node_position(graph, row, column);

			create_edges(graph, node_index, node_position, random_data);
		}
	}
}

static void generate_wages(graph_t *graph, random_data_t *random_data)
{
	random_data->random_edges = BOOL_FALSE;

	generate_graph(graph, random_data);
}

static void generate_consistent(graph_t *graph, random_data_t *random_data)
{
	generate_graph(graph, random_data);

	while (!check_consistency(graph))
	{
		generate_graph(graph, random_data);
	}
}

static void generate_random(graph_t *graph, random_data_t *random_data)
{
	generate_graph(graph, random_data);
}

void generate(graph_t *graph, char *mode, double min_weight, double max_weight)
{
	random_data_t *random_data = initialize_rand(min_weight, max_weight);

	if (strcmp(mode, GENERATE_WAGES_MODE) == 0)
	{
		generate_wages(graph, random_data);
	}
	else if (strcmp(mode, GENERATE_RANDOM_MODE) == 0)
	{
		generate_random(graph, random_data);
	}
	else if (strcmp(mode, GENERATE_CONSISTENT_MODE) == 0)
	{
		generate_consistent(graph, random_data);
	}

	free(random_data);
}
