#include <stdlib.h>
#include <stdio.h>
#include "handle_files.h"
#include "graph.h"
#include "constants.h"

static char *double_buf_size(char *buf, int *buf_size)
{
	*buf_size *= 2;
	return realloc(buf, *buf_size * sizeof *buf);
}

static int add_to_matrix(graph_t *graph, char *buf, int row)
{
	int node_index;
	int read_characters = 0;
	double value;
	char *line = buf;

	while (sscanf(line, "%d :%lf%n", &node_index, &value, &read_characters) == 2)
	{
		if (node_index < 0 || node_index >= graph->nodes_count)
		{
			fprintf(stderr, INVALID_FILE_FORMAT_ERROR);
			return BOOL_FALSE;
		}

		graph->matrix[row][node_index] = value;

		line += read_characters;
	}

	return BOOL_TRUE;
}

static void add_size(graph_t *graph, int rows, int columns)
{
	graph->rows = rows;
	graph->columns = columns;
	graph->nodes_count = rows * columns;
}

static int read_graph(FILE *in, graph_t *graph)
{
	int row = -1;
	int i = 0;
	char c;

	int buf_size = BUF_SIZE;
	char *buf = malloc(buf_size * sizeof *buf);

	if (buf == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		return BOOL_FALSE;
	}

	while ((c = fgetc(in)))
	{

		if (i + 2 >= buf_size)
		{
			buf = double_buf_size(buf, &buf_size);
		}

		if (c != EOF)
		{
			buf[i] = c;
		}

		if (row > -1 && (c == '\n' || c == EOF))
		{
			buf[i + 1] = '\0';

			if (!add_to_matrix(graph, buf, row))
			{
				free(buf);
				return BOOL_FALSE;
			}
		}

		if (c == '\n')
		{
			row++;
			i = -1;
		}
		else if (c == EOF)
		{
			break;
		}

		i++;
	}

	free(buf);

	return BOOL_TRUE;
}

static void write_size(FILE *out, graph_t *graph)
{
	fprintf(out, "%d %d\n", graph->rows, graph->columns);
}

static void write_graph(FILE *out, graph_t *graph)
{
	for (int i = 0; i < graph->nodes_count; i++)
	{
		fprintf(out, "\t");

		for (int j = 0; j < graph->nodes_count; j++)
		{
			if (graph->matrix[i][j] != NO_EDGE)
			{
				fprintf(out, "%d :%lf  ", j, graph->matrix[i][j]);
			}
		}

		fprintf(out, "\n");
	}
}

graph_t *read_file(char *filename)
{
	FILE *in = fopen(filename, "r");
	int rows, columns;

	if (in == NULL)
	{
		fprintf(stderr, FILE_STREAM_ERROR);
		return NULL;
	}

	if (fscanf(in, "%d %d", &rows, &columns) != 2)
	{
		fprintf(stderr, INVALID_FILE_FORMAT_ERROR);
		fclose(in);
		return NULL;
	}

	graph_t *graph = initialize(rows, columns);

	add_size(graph, rows, columns);

	if (!read_graph(in, graph))
	{
		fclose(in);
		return NULL;
	}

	fclose(in);

	return graph;
}

int write_file(graph_t *graph, char *filename)
{
	FILE *out = fopen(filename, "w");

	if (out == NULL)
	{
		fprintf(stderr, FILE_STREAM_ERROR);
		return BOOL_FALSE;
	}

	write_size(out, graph);

	write_graph(out, graph);

	fclose(out);

	return BOOL_TRUE;
}
