#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define BIAS 1

#define N_LAYERS 3
#define I_N_NEURONS 2
#define H_N_NEURONS 2
#define O_N_NEURONS 1

typedef enum layer_type {
	INPUT,
	HIDDEN,
	OUTPUT,
} layer_type;

#endif