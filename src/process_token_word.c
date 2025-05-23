#include "../includes/mini.h"

// not completed; u should check if the token comes from expansion ! or is_empty_expanded_var? 
int process_token_word(size_t *splt_arg_index, t_shell *shell, t_input *current_token, t_command_data *cmds)
{
	if (current_token->string[0] != '\0')
	{
		if (cmds->cmd_splitted == NULL)
		{
			cmds->cmd_splitted = ft_calloc((1 + count_cmds_tokens(current_token)), sizeof(char *));
			cmds->cmd_splitted[*splt_arg_index] = ft_strdup(current_token->string);
			// maybe u should check if token is quoted like: if (token->quoted == true) cmd->was_quoted = true;
			return (0);
		}
	}
	return (1);
}
