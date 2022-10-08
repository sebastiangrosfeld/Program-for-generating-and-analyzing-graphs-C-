#ifndef _RANDOM_H_
#define _RANDOM_H_

typedef struct random
{
	double min_weight;
	double max_weight;
	int random_edges;
} random_data_t;

random_data_t *initialize_rand(double min_weight, double max_weight);

double random_weight(random_data_t *random_data);

int random_edge();

#endif
