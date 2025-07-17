#include "../headers/funcs.h"

void	node_data(Node* node)
{
	printf("node inputs :\n");
	for (size_t i = 0; i < node->n_inputs; ++i)
	{
		printf("%f -", node->input[i]);
	}
	printf("\nnode weights :\n");
	for (size_t i = 0; i < node->n_inputs; ++i)
	{
		printf("%f -", node->weight[i]);
	}
	printf("\nnode output =  %f\n---------------------\n", node->output);
}

void	layer_data(Layer* l)
{
	for (size_t i = 0; i < l->n_nodes; ++i)
	{
		node_data(l->nodes[i]);
	}
}

//--------------------------------

double relu(double n)
{
	return (n <= 0 ? 0 : n);
}

double sigmoid(double n) // for binary output
{
	return (1 / (1 + pow(EULER_NUMBER, -n)));
}

double	sigmoid_derivative(double n)
{
    return (sigmoid(n) * (1.0 - sigmoid(n)));
}

double	xavier_init(size_t n_inputs)
{
	return ((double)rand() / RAND_MAX * 2.0 - 1.0) * sqrt(1.0 / n_inputs);
}

//------------------------------------

Node*	init_node(size_t n_inputs, double bias)
{
	Node* res = gb_malloc(1, sizeof(Node), ALLOC);
	res->bias = bias;
	res->n_inputs = n_inputs;
	res->input = gb_malloc(n_inputs, sizeof(double), ALLOC);
	res->weight = gb_malloc(n_inputs, sizeof(double), ALLOC);
	res->output = 0;

	for (size_t i = 0; i < n_inputs; ++i)
	{
		res->weight[i] = xavier_init(n_inputs);
	}

	return (res);
}

Layer*	init_layer(layer_type t, size_t n_nodes, size_t prev_n_nodes)
{
	Layer* res = gb_malloc(1, sizeof(Layer), ALLOC);
	res->nodes = gb_malloc(n_nodes + 1, sizeof(Node*), ALLOC);
	res->n_nodes = n_nodes;
	res->t = t;
	res->next = NULL;
	res->back = NULL;

	for (size_t i = 0; i < res->n_nodes; ++i)
	{
		res->nodes[i] = init_node(prev_n_nodes, BIAS);
	}

	return (res);
}

NN*	init_nn(size_t n_layers,
			size_t n_input, size_t n_hidden, size_t n_output,
			void* hidden_activ, void* output_activ)
{
	NN* res = gb_malloc(1, sizeof(NN), ALLOC);
	res->n_layers = n_layers;
	res->layers = gb_malloc(n_layers + 1, sizeof(Layer*), ALLOC);

	for (size_t i = 0; i < n_layers; ++i)
	{
		if (i == 0) // input
		{
			res->layers[i] = init_layer(INPUT, n_input, 1);
			res->layers[i]->layer_activ = NULL;
		}
		else if (i == n_layers - 1) // output
		{
			res->layers[i] = init_layer(OUTPUT, n_output, n_hidden);
			res->layers[i]->layer_activ = output_activ;
		}
		else // hidden
		{
			if (i - 1 == 0)
				res->layers[i] = init_layer(HIDDEN, n_hidden, n_input);
			else
				res->layers[i] = init_layer(HIDDEN, n_hidden, n_hidden);
			res->layers[i]->layer_activ = hidden_activ;
		}
	}

	// init back and forth pointers between layers

	for (size_t i = 0; i < n_layers - 1; ++i)
		res->layers[i]->next = res->layers[i + 1];
	for (size_t i = n_layers - 1; i > 0; --i)
		res->layers[i]->back = res->layers[i - 1];

	// set usefull pointers

	res->input_layer = res->layers[0];
	res->output_layer = res->layers[n_layers - 1];

	return (res);
}

//--------------------------------

void take_input(Layer* input_layer, double* sample)
{
    for (size_t i = 0; i < input_layer->n_nodes; ++i)
	{
        Node* cur_node = input_layer->nodes[i];
        cur_node->input[0] = sample[i];
    }
}

void	collect_output(Layer* l1, Layer* l2)
{
	for (size_t i = 0; i < l2->n_nodes; ++i)
	{
		Node* curr_node = l2->nodes[i];
		for (size_t j = 0; j < l1->n_nodes; ++j)
		{
			curr_node->input[j] = l1->nodes[j]->output;
		}
	}
}

void	compute_node(Node* n, double (*activ)(double))
{
	double res = 0;

	for (size_t i = 0; i < n->n_inputs; ++i)
	{
		res += n->weight[i] * n->input[i];
	}
	res += n->bias;
	if (activ)
		n->output = activ(res);
	else
		n->output = res;
}

void compute_layer(Layer* l)
{
    if (l->t == INPUT)
	{
        for (size_t i = 0; i < l->n_nodes; ++i)
		{
            Node* node = l->nodes[i];
            node->output = node->input[0];
        }
		return ;
    }
	collect_output(l->back, l);
	void*	activ = NULL;
	switch (l->t)
	{
		case OUTPUT:
			activ = sigmoid;
			break ;
		case HIDDEN:
			activ = relu;
			break ;
		case INPUT:
			break ;
	}
	for (size_t i = 0; i < l->n_nodes; ++i)
	{
		compute_node(l->nodes[i], activ);
	}
}

void	forward_propagation(NN* nn, double* data)
{
	if (nn->n_layers < 3)
	{
		fprintf(stderr, "need at least 3 layers\n");
		exit(1);
	}
	take_input(nn->input_layer, data);
	for (size_t i = 0; i < nn->n_layers; ++i)
	{
		compute_layer(nn->layers[i]);
	}
}

double	MeanSquaredError(NN* nn, double* true_data)
{
    Layer* last_layer = nn->output_layer;
    size_t n_outputs = last_layer->n_nodes;
    Node** last_layer_nodes = last_layer->nodes;
    double mse = 0;

    for (size_t i = 0; i < n_outputs; ++i)
    {
        double diff = last_layer_nodes[i]->output - true_data[i];
		// we square the diff to eliminate the negative and to enriche the value
        mse += diff * diff;
    }

    mse /= n_outputs;

    return (mse);
}

void	CalculateDelta(NN* nn, double* true_data)
{
	Layer* output_layer = nn->output_layer;

	for (size_t i = 0; i < output_layer->n_nodes; ++i)
	{
		Node* node = output_layer->nodes[i];
		node->delta = (node->output - true_data[i]) * sigmoid_derivative(node->output);
	}
}

void BackpropagateHiddenLayers(NN* nn)
{
    // Start from the layer before the output layer, going backwards
	Layer* i = nn->output_layer->back;
    while (i->t != INPUT) // Exclude input layer (index 0)
    {
        Layer* current_layer = i;
        Layer* next_layer = i->next;

        // For each node in the current layer
        for (size_t j = 0; j < current_layer->n_nodes; j++)
        {
            Node* current_node = current_layer->nodes[j];
            double sum_delta = 0.0;

            // Sum up all delta contributions from the next layer
            for (size_t k = 0; k < next_layer->n_nodes; k++)
            {
                Node* next_node = next_layer->nodes[k];
                // Weight from current node to the next layer node * delta of that node
                sum_delta += next_node->weight[j] * next_node->delta;
            }
            
            // Calculate delta for current node - depends on activation function
            if (current_layer->layer_activ == relu)
            {
                // Derivative of ReLU is 1 if output > 0, otherwise 0
                current_node->delta = sum_delta * (current_node->output > 0 ? 1.0 : 0.0);
            }
            else if (current_layer->layer_activ == sigmoid)
            {
                current_node->delta = sum_delta * sigmoid_derivative(current_node->output);
            }
        }
		i = i->back;
    }
}

void UpdateWeights(NN* nn, double learning_rate)
{
    // Skip the input layer (i=0) since it doesn't have incoming weights to update
    for (size_t i = 1; i < nn->n_layers; i++)
    {
        Layer* current_layer = nn->layers[i];

        // For each node in the current layer
        for (size_t j = 0; j < current_layer->n_nodes; j++)
        {
            Node* node = current_layer->nodes[j];
            // Update weights
            for (size_t k = 0; k < node->n_inputs; k++)
            {
                // Gradient descent update rule: w = w - learning_rate * delta * input
                node->weight[k] -= learning_rate * node->delta * node->input[k];
            }
            // Update bias
            node->bias -= learning_rate * node->delta;
        }
    }
}

void Backpropagate(NN* nn, double* true_data)
{
    // 1. Calculate delta for output layer
    CalculateDelta(nn, true_data);
    
    // 2. Backpropagate error to hidden layers
    BackpropagateHiddenLayers(nn);
    
    // 3. Update weights and biases
    UpdateWeights(nn, L_RATE);
}