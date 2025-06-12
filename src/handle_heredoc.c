/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:12:17 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:19:35 by aeleimat         ###   ########.fr       */
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

int	handle_heredoc(t_shell *shell, t_input **token, t_command_data **cmd,
		int *cmd_i)
{
	if (FT)
	{
		cmd[*cmd_i]->content_analyze.is_there_heredoc = true;
		*token = (*token)->next;
		cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc]
			= ft_strdup((*token)->string);
		cmd[*cmd_i]->delim[cmd[*cmd_i]->index_of_heredoc + 1] = NULL;
	}
	return (increase_heredoc_index(cmd, cmd_i));
}
