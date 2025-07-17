#include "../headers/types.h"
#include "../headers/funcs.h"
#include "../headers/macro.h"
#include "../headers/garbage.h"
#include "../headers/utils.h"

//----------------mock data generation-------------

double** create_test_data(size_t num_samples, size_t input_size)
{
    double** test_data = gb_malloc(num_samples + 1, sizeof(double*), ALLOC);
    for (size_t i = 0; i < num_samples; ++i)
	{
        test_data[i] = gb_malloc(input_size, sizeof(double), ALLOC);
        for (size_t j = 0; j < input_size; ++j)
		{
            test_data[i][j] = (double)rand() / RAND_MAX;
        }
    }
    return (test_data);
}

double* create_test_output(size_t num_samples, size_t output_size)
{
    double* expected = gb_malloc(num_samples * output_size, sizeof(double), ALLOC);
    for (size_t i = 0; i < num_samples * output_size; ++i)
	{
        expected[i] = (double)rand() / RAND_MAX;
    }
    return (expected);
}

//----------------------------------------------

void test_network(NN* network, double** test_data, double* expected_outputs, 
                 size_t num_samples, size_t output_size) {
    double total_error = 0.0;
    
    printf("Testing neural network with %zu samples:\n", num_samples);
    
    for (size_t i = 0; i < num_samples; ++i)
	{
        forward_propagation(network, test_data[i]);
        
        // Print inputs
        printf("\nSample %zu\n", i + 1);
        printf("Inputs: ");
        print_vector(test_data[i], network->input_layer->n_nodes);

        // Get and print outputs
        double* outputs = gb_malloc(output_size, sizeof(double), ALLOC);
        for (size_t j = 0; j < output_size; ++j)
		{
            outputs[j] = network->output_layer->nodes[j]->output;
        }

        printf("Network outputs: ");
        print_vector(outputs, output_size);

        printf("Expected outputs: ");
        print_vector(&expected_outputs[i * output_size], output_size);

        // Calculate error for this sample
        double sample_error = 0.0;
        for (size_t j = 0; j < output_size; ++j)
		{
            double diff = outputs[j] - expected_outputs[i * output_size + j];
            sample_error += diff * diff;
        }

        sample_error /= output_size;
        total_error += sample_error;

        printf("Sample error: %f\n", sample_error);
    }

    double avg_error = total_error / num_samples;
    printf("\nAverage error across all test samples: %f\n", avg_error);
}



int main() {
    srand(time(NULL));

    NN* network = init_nn(N_LAYERS, I_N_NEURONS, H_N_NEURONS, O_N_NEURONS, sigmoid, relu);
    
    double** test_data = create_test_data(N_TESTS, I_N_NEURONS);
    double* expected_outputs = create_test_output(N_TESTS, O_N_NEURONS);

    printf("Training network ...\n");
    for (int epoch = 0; epoch < NUM_EPOCHS; ++epoch)
	{
        for (size_t i = 0; i < N_TESTS; ++i)
		{
            forward_propagation(network, test_data[i]);
            back_propagate(network, &expected_outputs[i * O_N_NEURONS]);
        }
    }

    test_network(network, test_data, expected_outputs, N_TESTS, O_N_NEURONS);

    gb_malloc(0, 0, CLEAR);
    return 0;
}