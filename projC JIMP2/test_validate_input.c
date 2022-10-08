#include <stdlib.h>
#include <stdio.h>
#include "validate_input.h"
#include "constants.h"

int main(int argc, char **argv)
{
	if (!validate_input(argc, argv))
	{
		printf(TEST_PASSED);
	}
	else
	{
		printf(TEST_FAILED);
	}

	printf("\n");

	return EXIT_SUCCESS;
}
