#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "handle_files.h"
#include "graph.h"
#include "dijkstra.h"
#include "constants.h"

int main(int argc, char **argv)
{
	if (!atoi(argv[3]))
	{
		graph_t *graph = read_file(argv[1]);

		if (graph == NULL)
		{
			fprintf(stderr, FILE_STREAM_ERROR);
			return EXIT_FAILURE;
		}

		find_path(graph, 0, 3);
		find_path(graph, 0, 9);
		find_path(graph, 10, 2);
		find_path(graph, 0, 1);

		free_graph(graph);

		return EXIT_SUCCESS;
	}

	FILE *results = fopen("test_dijkstra_results.txt", "r");

	if (results == NULL)
	{
		fprintf(stderr, FILE_STREAM_ERROR);
		return EXIT_FAILURE;
	}

	FILE *expected = fopen("test_files/dijkstra_test_expected.txt", "r");

	if (expected == NULL)
	{
		fprintf(stderr, FILE_STREAM_ERROR);
		fclose(results);
		return EXIT_FAILURE;
	}

	printf("It should find shortest paths\n");

	char results_c;
	char expected_c;

	while ((expected_c = fgetc(expected)) != EOF)
	{
		results_c = fgetc(results);

		if (results_c == EOF || results_c != expected_c)
		{
			printf(TEST_FAILED);
			fclose(results);
			fclose(expected);
			return EXIT_SUCCESS;
		}
	}

	printf(TEST_PASSED);

	fclose(results);
	fclose(expected);

	return EXIT_SUCCESS;
}
