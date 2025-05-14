#include "../includes/mini.h"

void	input_handler(t_shell *shell, int i, int j)
{
	int	i;

	if (!shell || !shell->someone.args)
		return ;
	i = 0;
	while (test->split_the_split[i])
	{
		if (test->split_the_split[i][0] == NULL)
		{
			i++;
			break ;
		}
		if (ft_strcmp(test->split_the_split[i][0], "export") == 0)
		{
			i++;
			continue ;
		}
		expand_tokens_in_row(&(test->split_the_split[i]), test);
		i++;
	}
}