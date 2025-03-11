#include "types.h"
#include "funcs.h"
#include "macro.h"
#include "garbage.h"

double*	rand_data(size_t size)
{
	double* res = gb_malloc(size, sizeof(double), ALLOC);
	for (size_t i = 0; i < size; ++i)
	{
		res[i] = rand() / 100000;
	}
	return (res);
}

int main ()
{
	srand(time(NULL));

	double* data = rand_data(I_N_NEURONS);
	NN* test = init_nn(N_LAYERS, I_N_NEURONS, H_N_NEURONS, O_N_NEURONS);
	forward_propagation(test, data);

	layer_data(test->input_layer);
	layer_data(test->output_layer);

	gb_malloc(0, 0, CLEAR);
	return (0);
}