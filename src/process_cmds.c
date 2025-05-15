#include "../includes/mini.h"
  

handler_of_tokens

void	process_cmds(t_shell *shell, int i , int j)
{
	size_t	iterator;
	size_t cmd_iterator;

	iterator = 0;
	cmd_iterator = 0;
	while (j && NULL != shell->tokens->string)
	{
		if (!handler_of_tokens(&iterator, &cmd_iterator, shell))
			return (0);
	}
	return (1);

}