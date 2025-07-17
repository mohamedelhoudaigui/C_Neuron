#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define BIAS 1

#define DATA_X 4
#define DATA_Y 1

#define N_LAYERS 3
#define I_N_NEURONS DATA_X
#define H_N_NEURONS 4
#define O_N_NEURONS DATA_X

#define EULER_NUMBER 2.71828

#define L_RATE 0.1


typedef enum layer_type {
	INPUT,
	HIDDEN,
	OUTPUT,
} layer_type;

#endif