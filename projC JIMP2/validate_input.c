#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "validate_input.h"
#include "constants.h"

static int handle_invalid_mode()
{
	fprintf(stderr, "Invalid mode\n");
	return BOOL_FALSE;
}

static int handle_invalid_arguments_count()
{
	fprintf(stderr, "Invalid number of arguments\n");
	return BOOL_FALSE;
}

static int validate_generate_arguments(int argc, char **argv)
{
	int rows = atoi(argv[3]);
	int columns = atoi(argv[4]);
	double min_wage = atof(argv[5]);
	double max_wage = atof(argv[6]);

	int error_occured = BOOL_FALSE;

	if (rows <= 0)
	{
		fprintf(stderr, "Number of rows must be greater than 0. Received %d\n", rows);
		error_occured = BOOL_TRUE;
	}

	if (columns <= 0)
	{
		fprintf(stderr, "Number of columns must be greater than 0. Received %d\n", columns);
		error_occured = BOOL_TRUE;
	}

	if (min_wage < 0)
	{
		fprintf(stderr, "Min wage must be greater than or equal 0. Received %g\n", min_wage);
		error_occured = BOOL_TRUE;
	}

	if (max_wage < 0)
	{
		fprintf(stderr, "Max wage must be greater than or equal 0. Received %g\n", max_wage);
		error_occured = BOOL_TRUE;
	}

	if (max_wage <= min_wage)
	{
		fprintf(stderr, "Max wage must be greater than min wage. Received min wage = %g and max wage = %g\n", min_wage, max_wage);
		error_occured = BOOL_TRUE;
	}

	return !error_occured;
}

static int validate_analyze_arguments(int argc, char **argv)
{
	int error_occured = BOOL_FALSE;

	for (int i = 4; i < argc; i += 2)
	{
		int source = atoi(argv[i - 1]);
		int destination = atoi(argv[i]);

		if (source < 0)
		{
			fprintf(stderr, "Source must be greater than or equal 0. Received %d\n", source);
			error_occured = BOOL_TRUE;
		}

		if (destination < 0)
		{
			fprintf(stderr, "Destination must be greater than or equal 0. Received %d\n", destination);
			error_occured = BOOL_TRUE;
		}

		if (source == destination)
		{
			fprintf(stderr, "Source must not be equal destination. Received source = %d and destination = %d\n", source, destination);
			error_occured = BOOL_TRUE;
		}
	}

	return !error_occured;
}

static int validate_generate_mode(int argc, char **argv)
{
	if (argc != 7)
	{
		return handle_invalid_arguments_count();
	}

	return validate_generate_arguments(argc, argv);
}

static int validate_analyze_mode(int argc, char **argv)
{
	if (argc < 3 || (argc - 3) % 2 != 0)
	{
		return handle_invalid_arguments_count();
	}

	return validate_analyze_arguments(argc, argv);
}

static int validate_mode(char *mode, int argc, char **argv)
{
	if (strcmp(mode, GENERATE_WAGES_MODE) == 0 || strcmp(mode, GENERATE_RANDOM_MODE) == 0 || strcmp(mode, GENERATE_CONSISTENT_MODE) == 0)
	{
		return validate_generate_mode(argc, argv) ? BOOL_TRUE : BOOL_FALSE;
	}
	else if (strcmp(mode, ANALYZE_MODE) == 0)
	{
		return validate_analyze_mode(argc, argv) ? BOOL_TRUE : BOOL_FALSE;
	}
	else
	{
		return handle_invalid_mode();
	}
}

int validate_input(int argc, char **argv)
{
	if (argc <= 2)
	{
		return handle_invalid_arguments_count();
	}

	return validate_mode(argv[1], argc, argv);
}
