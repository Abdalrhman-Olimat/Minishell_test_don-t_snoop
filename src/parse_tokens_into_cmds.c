#include "../includes/mini.h"
  

static t_shell_returns handle_pipe_problem(t_shell *shell, t_input *token, t_command_data **cmd, int *cmd_i)
{
	if (FT)
		if (token->next->string == NULL)
		{
			// ft_putstr_fd("Error after Pipe; not completed command\n", 2); 
			shell->exit_status = 2;
			return (0);
		}
	if (FT)
		cmd[*cmd_i]->content_analyze.is_there_pipe = true;
	// cmd[++*cmd_i]->cmd_full[0] = '\0';
	return (2);

}


static t_shell_returns handle_tokens_into_cmds(t_shell *shell, t_input *tokens, int *itereator_of_cmd)
{
	// 1 - 	handler pipe problem
	if (true == shell->cmds[*itereator_of_cmd]->skip_cmd)
	{
		if (shell->tokens->type == TYPE_PIPE)
			if (!handle_pipe_problem(shell, tokens, &shell->cmds[*itereator_of_cmd], itereator_of_cmd))
				return (0);
		return (2);
	}
	// 2- 	Handler of words :  // this function will handle the commands and concat them in *string
		// 
		//
	else if (shell->tokens->type == TYPE_WORD)
	{
		words_to_cmd(shell, tokens, shell->cmds, itereator_of_cmd);
	}
	// 3-	Handler of cmds from expansion. 		// TODO
	/*
		 The from_expansion flag indicates that the token did not come directly from the user's input,
		  but was generated after expanding something like $VAR or a similar construct.
		  
		  TEST IT.
	*/
	// else if (is_from_expansion && tokens->string[0] = '|')
		// return handle_pipe_with_expansion(shell, tokens, shell->cmds, itereator_of_cmd);

	// 4-	Handler of Token PIPES
	else if (tokens->type == TYPE_PIPE)
	{
		if (!handle_pipe_problem(shell, tokens, shell->cmds, itereator_of_cmd))
			return (0);
	}
	// 5-	Handler of Token redirections
	else if (tokens->type == TYPE_REDIR_IN)
	{
		handle_redir_in(shell, tokens, itereator_of_cmd, shell->cmds);
	}
	else if (tokens->type == TYPE_REDIR_OUT)
	{
		handle_redir_out(shell, tokens, shell->cmds, itereator_of_cmd);
	}
	// 6-	Handler of Token Append
	else if (tokens->type == TYPE_APPEND)
	{
		handle_append(shell, tokens, shell->cmds, itereator_of_cmd);
	}
	else if (tokens->type == TYPE_HEREDOC)
	{
		handle_heredoc(shell, tokens, shell->cmds, itereator_of_cmd);
	}
	return 3;
}


int	parse_tokens_into_cmds(t_shell *shell, t_input **tokens, int i , int j)
{
	int cmds_iterator;

	*tokens = shell->tokens;
	cmds_iterator = 0;
	
	if (FT > 0)
		while ((j + i) && NULL != shell->tokens->string)
		{
			if (!handle_tokens_into_cmds(shell, *tokens, &cmds_iterator))
				return (0);
			tokens = &(*tokens)->next;
		}
	return (1);
}