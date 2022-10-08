#include <stdio.h>
#include "help.h"

void print_help()
{
	printf("Grapher is a software that can generate graph and analyze them\n\n");
	printf("Usage\n\n");
	printf("There are 4 work modes: generate_wages, generate_consistent, generate_random, analyze\n\n");
	printf("Usage for generate_wages mode:\n");
	printf("./grapher generate_wages filename rows columns min_wage max_wage\n\n");
	printf("Usage for generate_consistent mode:\n");
	printf("./grapher generate_consistent filename rows columns min_wage max_wage\n\n");
	printf("Usage for generate_random mode:\n");
	printf("./grapher generate_random filename rows columns min_wage max_wage\n\n");
	printf("Usage for analyze mode:\n");
	printf("./grapher analyze filename [source] [destination] [source(1)] [destination(2)] ...\n\n");
}
