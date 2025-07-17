#ifndef GARBAGE_H
#define GARBAGE_H

#include <stdlib.h>

#define ALLOC 0
#define CLEAR 1
#define ADDR_NUM 256 * 256 * 256

void	*gb_malloc(size_t count, size_t size, int type);

#endif