#include "../includes/mini.h"

int process_token_word(size_t *splt_arg_index, t_shell *shell, t_input *current_token, t_command_data *cmds)
{
	if (current_token->string[0] != '\0')
	{
		if (cmds->cmd_splitted == NULL)
		{
			cmds->cmd_splitted = ft_calloc((1 + count_cmds_tokens(current_token)), sizeof(char *));
			return (0);
		}
	}
	return (1);
}
