/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_into_cmds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:32:10 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:54:10 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static t_shell_returns	handle_pipe_problem(t_shell *shell, t_input *token,
		t_command_data **cmd, int *cmd_i)
{
	if (FT)
	{
		if (token->next->string == NULL)
		{
			shell->exit_status = 2;
			return (0);
		}
	}
	if (FT)
	{
		cmd[*cmd_i]->content_analyze.is_there_pipe = true;
		cmd[++*cmd_i]->cmd_full[0] = '\0';
	}
	return (2);
}

static int	handle_redirection(t_shell *shell, t_input **tokens,
		int *itereator_of_cmd)
{
	advanced_symbols_check(shell, tokens, itereator_of_cmd);
	if ((*tokens)->type == TYPE_REDIR_IN)
	{
		handle_redir_in(shell, tokens, itereator_of_cmd, shell->cmds);
	}
	else if ((*tokens)->type == TYPE_REDIR_OUT)
	{
		handle_redir_out(shell, tokens, shell->cmds, itereator_of_cmd);
	}
	else if ((*tokens)->type == TYPE_APPEND)
	{
		handle_append(shell, tokens, shell->cmds, itereator_of_cmd);
	}
	else if ((*tokens)->type == TYPE_HEREDOC)
	{
		handle_heredoc(shell, tokens, shell->cmds, itereator_of_cmd);
	}
	return (1);
}

static bool	is_redirection_token(int token_type)
{
	return (token_type == TYPE_REDIR_IN || token_type == TYPE_REDIR_OUT
		|| token_type == TYPE_APPEND || token_type == TYPE_HEREDOC);
}

static t_shell_returns	handle_tokens_into_cmds(t_shell *shell,
												t_input **tokens,
												int *itereator_of_cmd)
{
	if (true == shell->cmds[*itereator_of_cmd]->skip_cmd)
	{
		if ((*tokens)->type == TYPE_PIPE)
			if (!handle_pipe_problem(shell, *tokens,
					&shell->cmds[*itereator_of_cmd], itereator_of_cmd))
				return (0);
		return (2);
	}
	else if ((*tokens)->type == TYPE_WORD)
	{
		words_to_cmd(shell, *tokens, shell->cmds, itereator_of_cmd);
	}
	else if ((*tokens)->type == TYPE_PIPE)
	{
		if (!handle_pipe_problem(shell, *tokens, shell->cmds, itereator_of_cmd))
			return (0);
	}
	else if (is_redirection_token((*tokens)->type))
	{
		if (!handle_redirection(shell, tokens, itereator_of_cmd))
			return (0);
	}
	return (3);
}

int	parse_tokens_into_cmds(t_shell *shell, t_input **tokens, int i, int j)
{
	int	cmds_iterator;

	*tokens = shell->tokens;
	cmds_iterator = 0;
	if (FT > 0)
	{
		while ((j + i) && *tokens != NULL)
		{
			if (!handle_tokens_into_cmds(shell, tokens, &cmds_iterator))
				return (0);
			tokens = &(*tokens)->next;
		}
	}
	return (1);
}
