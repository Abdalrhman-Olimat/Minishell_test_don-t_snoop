#include "../includes/mini.h"

void	free_2d_arr(char **string)
{
	int	i;

	if (!string)
		return ;
	i = 0;
	if (string)
		while (string[i])
		{
			free(string[i]);
			i++;
		}
	free(string);
}

