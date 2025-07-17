#include "../headers/types.h"
#include "../headers/funcs.h"
#include "../headers/macro.h"
#include "../headers/garbage.h"
#include "../headers/utils.h"

//----------------mock data generation-------------

double**	rand_data(size_t y, size_t x)
{
	double** res = gb_malloc(y + 1, sizeof(double*), ALLOC);
	for (size_t i = 0; i < y; ++i)
	{
		res[i] = gb_malloc(x, sizeof(double), ALLOC);
		for (size_t j = 0; j < x; ++j)
		{
			res[i][j] = (double)rand() / RAND_MAX;
		}
	}
	return (res);
}

double*	true_data(size_t x)
{
	double* res = gb_malloc(x, sizeof(double), ALLOC);
	for (size_t i = 0; i < x; ++i)
	{
		res[i] = (double)rand() / RAND_MAX;
	}
	return (res);
}

//-----------------------------------------------


int main ()
{
	srand(time(NULL));

	double**	data = rand_data(DATA_Y, DATA_X);
	double*		t_data = true_data(DATA_X);

	NN* test = init_nn(N_LAYERS,
						I_N_NEURONS, H_N_NEURONS, O_N_NEURONS,
						sigmoid, relu);


	double total_error = 0;
	for (int epoch = 0; epoch < NUM_EPOCHS; ++epoch) {
		total_error = 0;
		for (int i = 0; i < DATA_Y; ++i) {
			forward_propagation(test, data[i]);
			double error = mean_squared_error(test, t_data);
			total_error += error;
			back_propagate(test, t_data);
		}
		printf("Epoch %d, Total Error: %f\n", epoch, total_error);
	}


	gb_malloc(0, 0, CLEAR);
	return (0);
}