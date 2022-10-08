#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "validate_input.h"
#include "graph.h"
#include "generate.h"
#include "bfs.h"
#include "dijkstra.h"
#include "handle_files.h"
#include "help.h"
#include "constants.h"

int main(int argc, char **argv)
{
	char *mode = argv[1];
	char *filename = argv[2];

	graph_t *graph;

	if (strcmp(mode, HELP) == 0)
	{
		print_help();
		return EXIT_SUCCESS;
	}

	if (!validate_input(argc, argv))
	{
		print_help();
		return EXIT_FAILURE;
	}

	if (strcmp(mode, ANALYZE_MODE) == 0)
	{
		graph = read_file(filename);

		if (graph == NULL)
		{
			return EXIT_FAILURE;
		}

		if (check_consistency(graph))
		{
			printf("\n");

			for (int i = 4; i < argc; i += 2)
			{
				int source = atoi(argv[i - 1]);
				int destination = atoi(argv[i]);

				if (!find_path(graph, source, destination))
				{
					free_graph(graph);
					return EXIT_FAILURE;
				}
			}
		}
	}
	else
	{
		int rows = atoi(argv[3]);
		int columns = atoi(argv[4]);
		double min_weight = atof(argv[5]);
		double max_weight = atof(argv[6]);

		graph = initialize(rows, columns);

		if (graph == NULL)
		{
			return EXIT_FAILURE;
		}

		generate(graph, mode, min_weight, max_weight);

		if (!write_file(graph, filename))
		{
			free_graph(graph);
			return EXIT_FAILURE;
		}
	}

#ifdef DEBUG
	print_graph(graph);
#endif

	free_graph(graph);

	return EXIT_SUCCESS;
}
