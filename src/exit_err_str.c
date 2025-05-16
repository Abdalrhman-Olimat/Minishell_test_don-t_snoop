#include "../includes/mini.h"

void	exit_err_str(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}