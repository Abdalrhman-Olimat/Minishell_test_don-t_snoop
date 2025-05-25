#include "../includes/mini.h"

int	get_2d_len(char **arr)
{
	int	i = 0;

	while (arr && arr[i])
		i++;
	return (i);
}