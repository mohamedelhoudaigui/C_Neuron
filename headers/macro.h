#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define BIAS 0.1

#define DATA_X 10
#define DATA_Y 10

#define N_LAYERS 10
#define I_N_NEURONS DATA_X
#define H_N_NEURONS 10
#define O_N_NEURONS 1

#define EULER_NUMBER 2.71828

#define L_RATE 0.01
#define NUM_EPOCHS 1000
#define N_TESTS 100


typedef enum layer_type {
	INPUT,
	HIDDEN,
	OUTPUT,
} layer_type;

#endif