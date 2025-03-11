#ifndef FUNCS_H
#define FUNCS_H

#include "types.h"
#include "macro.h"
#include "garbage.h"



Node*	init_node(size_t n_inputs, double bias);
Layer*	init_layer(layer_type t, size_t n_nodes, size_t prev_n_nodes);
NN*		init_nn(size_t n_layers, size_t n_input, size_t n_hidden, size_t n_output);

void	take_input(Layer* input_layer, double* data, size_t data_size);
void	collect_output(Layer* l1, Layer* l2);
void	compute_node(Node* n);
void	compute_layer(Layer* l);
void	forward_propagation(NN* nn, double* data);

double	relu(double n);
double	xavier_init(size_t n_inputs);

void	node_data(Node* node);
void	layer_data(Layer* l);

#endif
