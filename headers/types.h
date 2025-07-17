#ifndef TYPES_H
#define TYPES_H

#include "macro.h"


typedef struct Node {
	double*	input;
	double*	weight;

	double	bias;
	double	output;
	double	delta; // for ouput node

	size_t n_inputs;
}	Node;

typedef struct	Layer {
	Node**	nodes;
	struct Layer* next;
	struct Layer* back;
	double (*layer_activ) (double n);
	size_t	n_nodes;
	layer_type t;

}	Layer;

typedef struct Neuron_Network {
	Layer**	layers;
	Layer*	input_layer;
	Layer*	output_layer;
	size_t	n_layers;

}	NN;

#endif