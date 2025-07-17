#include "../headers/garbage.h"


static void clear_mem(void* mem_arr[], int* i)
{
	while (*i >= 0)
	{
		free(mem_arr[*i]);
		*i = *i - 1;
	}
	*i = 0;
}

void	*gb_malloc(size_t count, size_t size, int type)
{
	static void		*mem_arr[ADDR_NUM] = {0};
	static int	i = 0;
	void			*addr = NULL;

	switch (type)
	{
		case CLEAR:
			clear_mem(mem_arr, &i);
			break ;
		case ALLOC:
			if (!(addr = calloc(count, size)))
			{
				clear_mem(mem_arr, &i);
				exit(2);
			}
			mem_arr[i++] = addr;
			return (addr);
	}
	return (NULL);
}