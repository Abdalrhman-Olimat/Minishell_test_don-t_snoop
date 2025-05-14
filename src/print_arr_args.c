#include "../includes/mini.h"

void	print_args(char **args)
{
	int	i;

	if (!args)
	{
		printf("Args: (null)\n");
		return;
	}
	i = 0;
	while (args[i])
	{
		printf("Arg[%d]: \"%s\"\n", i, args[i]);
		i++;
	}
}