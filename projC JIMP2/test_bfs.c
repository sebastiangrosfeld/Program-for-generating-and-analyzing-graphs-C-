#include <stdlib.h>
#include <stdio.h>
#include "handle_files.h"
#include "graph.h"
#include "bfs.h"
#include "constants.h"

int main(int argc, char **argv)
{
	graph_t *consistent_graph = read_file(argv[1]);
	graph_t *inconsistent_graph = read_file(argv[2]);

	printf("It should recognize graph as consistent\n");

	if (check_consistency(consistent_graph))
	{
		printf(TEST_PASSED);
	}
	else
	{
		printf(TEST_FAILED);
	}

	printf("\nIt should recognize graph as inconsistent\n");

	if (check_consistency(inconsistent_graph))
	{
		printf(TEST_FAILED);
	}
	else
	{
		printf(TEST_PASSED);
	}

	free_graph(consistent_graph);
	free_graph(inconsistent_graph);

	return EXIT_SUCCESS;
}
