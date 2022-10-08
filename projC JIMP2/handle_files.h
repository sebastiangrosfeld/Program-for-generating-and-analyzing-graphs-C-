#ifndef _HANDLE_FILES_H_
#define _HANDLE_FILES_H_

#include <stdio.h>
#include "graph.h"

#define BUF_SIZE 128 /* Initial buffer size for line reading */

static char *double_buf_size(char *buf, int *buf_size);

static int add_to_matrix(graph_t *graph, char *buf, int row);

static void add_size(graph_t *graph, int rows, int columns);

static int read_graph(FILE *in, graph_t *graph);

static void write_size(FILE *out, graph_t *graph);

static void write_graph(FILE *out, graph_t *graph);

graph_t *read_file(char *filename);

int write_file(graph_t *graph, char *filename);

#endif
