#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "random.h"
#include "constants.h"

random_data_t *initialize_rand(double min_weight, double max_weight)
{
	random_data_t *random_data = malloc(sizeof *random_data);

	if (random_data == NULL)
	{
		fprintf(stderr, ALLOCATION_ERROR);
		return NULL;
	}

	random_data->min_weight = min_weight;
	random_data->max_weight = max_weight;
	random_data->random_edges = BOOL_TRUE;

	srand(time(NULL));

	return random_data;
}

double random_weight(random_data_t *random_data)
{
	return random_data->min_weight + (random_data->max_weight - random_data->min_weight) * (double)rand() / RAND_MAX;
}

int random_edge()
{
	if (((double)rand() / (RAND_MAX + 1.0) * 100.0) <= EDGE_CHANCE)
	{
		return BOOL_TRUE;
	}

	return BOOL_FALSE;
}
