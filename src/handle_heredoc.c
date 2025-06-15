/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:12:17 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:12:53 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	increase_heredoc_index(t_command_data **cmd, int *cmd_i)
{
	if (NULL == cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc])
		return (0);
	else
	{
		cmd[*cmd_i]->index_of_heredoc++;
		return (1);
	}
}

static int	setup_default_cat_command(t_command_data *cmd)
{
	cmd->cmd_full = malloc(MAXIMUM_CMD_SIZE);
	if (!cmd->cmd_full)
		return (0);
	ft_memset(cmd->cmd_full, 0, MAXIMUM_CMD_SIZE);
	ft_strlcpy(cmd->cmd_full, "cat", MAXIMUM_CMD_SIZE);
	
	cmd->cmd_splitted = malloc(sizeof(char *) * 2);
	if (!cmd->cmd_splitted)
	{
		free(cmd->cmd_full);
		return (0);
	}
	cmd->cmd_splitted[0] = ft_strdup("cat");
	cmd->cmd_splitted[1] = NULL;
	return (1);
}

int	handle_heredoc(t_shell *shell, t_input **token, t_command_data **cmd,
		int *cmd_i)
{
	if (FT)
	{
		cmd[*cmd_i]->content_analyze.is_there_heredoc = true;
		if ((*token)->next == NULL)
		{
			cmd[*cmd_i]->skip_cmd = true;
			shell->exit_status = 2;
			return (0);
		}
		if (cmd[*cmd_i]->cmd_full == NULL || cmd[*cmd_i]->cmd_full[0] == '\0')
		{
			if (!setup_default_cat_command(cmd[*cmd_i]))
				return (0);
		}
		cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc] = ft_strdup((*token)->next->string);
		cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc + 1] = NULL;
	}
	return (increase_heredoc_index(cmd, cmd_i));
}
