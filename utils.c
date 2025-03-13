#include "utils.h"

void	print_vector(double* s, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		printf("%f - ", s[i]);
	}
	printf("\n");
}