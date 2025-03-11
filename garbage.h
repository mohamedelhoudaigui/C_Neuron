#ifndef GARBAGE_H
#define GARBAGE_H

#include <stdlib.h>
#include <string.h>

#define ALLOC 0
#define CLEAR 1

typedef struct s_garb
{
	void			*addr;
	struct s_garb	*next;
}				t_garb ;

void	clear_list(t_garb *list);
void	add_node(t_garb **list, t_garb *node);
void	*gb_malloc(size_t count, size_t size, int type);

#endif