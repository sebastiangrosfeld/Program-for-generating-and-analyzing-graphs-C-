#include <stdlib.h>
#include <stdio.h>
#include "handle_files.h"
#include "graph.h"
#include "generate.h"
#include "constants.h"
#include "bfs.h"

int main(int argc, char **argv)
{
	printf("It should initialize the graph\n");

	graph_t *graph = initialize(7, 4);

	if (graph == NULL)
	{
		printf("Graph initialization failure\n");
		printf(TEST_FAILED);
		return EXIT_SUCCESS;
	}

	printf(TEST_PASSED);

	printf("\nIt should generate consistent graph\n");

	generate(graph, GENERATE_WAGES_MODE, 0, 1);

	if (!check_consistency(graph))
	{
		printf("Generated graph is inconsistent\n");
		printf(TEST_FAILED);
		return EXIT_SUCCESS;
	}

	printf(TEST_PASSED);

	printf("\nIt should write graph to file\n");

	if (!write_file(graph, "test_graph_output.txt"))
	{
		printf("Failed to write a file\n");
		printf(TEST_FAILED);
		return EXIT_SUCCESS;
	}

	printf(TEST_PASSED);

	return EXIT_SUCCESS;
}
