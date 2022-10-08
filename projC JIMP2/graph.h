#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct graph
{
	int rows;		 /* number of rows */
	int columns;	 /* number of columns */
	int nodes_count; /* number of nodes */
	double **matrix; /* adjacency matrix */
} graph_t;

static int handle_row_allocation_error(graph_t *graph, int row_index);

static void initialize_matrix(graph_t *graph);

static int allocate_matrix_rows(graph_t *graph);

static int allocate_graph_matrix(graph_t *graph);

graph_t *initialize(int rows, int columns);

void free_graph(graph_t *graph);

void print_graph(graph_t *graph);

#endif
