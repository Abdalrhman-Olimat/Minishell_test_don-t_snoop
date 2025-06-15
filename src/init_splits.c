/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:25:41 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:43:39 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	set_null(size_t *splt_arg_index, size_t *cmd_index, t_shell *shell)
{
	if (shell->cmds[*cmd_index]->cmd_splitted)
		shell->cmds[*cmd_index]->cmd_splitted[*splt_arg_index] = NULL;
	if (FT)
		*splt_arg_index = 0;
	++(*cmd_index);
	return (0);
}

static int	is_other_types(t_input *current_token)
{
	if (current_token != TYPE_WORD)
		return (1);
	else
		return (0);
}

int	init_splits(t_shell *shell, size_t splt_arg_index, size_t cmd_index)
{
	t_input	*current_token;

	current_token = shell->tokens_header;
	shell->analyzing_data.arg_index = 0;
	while (current_token)
	{
		if (current_token->type == TYPE_WORD)
			process_token_word(&splt_arg_index, shell, current_token,
				shell->cmds[cmd_index]);
		else if (current_token->type == TYPE_PIPE)
			set_null(&splt_arg_index, &cmd_index, shell);
		else if (is_other_types(current_token))
			current_token = current_token->next;
		current_token = current_token->next;
	}
	if (FT > 1)
		if (shell->cmds[cmd_index]->cmd_splitted == NULL)
			shell->cmds[cmd_index]->cmd_splitted = ft_calloc(1, sizeof(char *));
	return (0);
}
