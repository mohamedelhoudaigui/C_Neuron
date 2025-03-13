#include "types.h"
#include "funcs.h"
#include "macro.h"
#include "garbage.h"

double**	rand_data(size_t y, size_t x)
{
	double** res = gb_malloc(y + 1, sizeof(double*), ALLOC);
	for (size_t i = 0; i < y; ++i)
	{
		res[i] = gb_malloc(x, sizeof(double), ALLOC);
		for (size_t j = 0; j < x; ++j)
		{
			res[i][j] = rand() / RAND_MAX;
		}
	}
	return (res);
}

int main ()
{
	srand(time(NULL));

	double** data = rand_data(DATA_Y, DATA_X);
	NN* test = init_nn(N_LAYERS, DATA_X, I_N_NEURONS, H_N_NEURONS, O_N_NEURONS);
	forward_propagation(test, data);

	layer_data(test->input_layer);
	layer_data(test->output_layer);

	gb_malloc(0, 0, CLEAR);
	return (0);
}