#include <stdlib.h>
#include <stdio.h>
#include "handle_files.h"
#include "graph.h"
#include "constants.h"

int main(int argc, char **argv)
{
	printf("It should print error on wrong file format\n");

	graph_t *graph = read_file(argv[1]);

	if (graph == NULL)
	{
		printf(TEST_PASSED);
	}
	else
	{
		printf(TEST_FAILED);
	}

	printf("\nIt should read graph from file\n");

	graph = read_file(argv[2]);

	if (graph == NULL)
	{
		printf(TEST_FAILED);
	}
	else
	{
		printf(TEST_PASSED);
		free_graph(graph);
	}

	return EXIT_SUCCESS;
}
