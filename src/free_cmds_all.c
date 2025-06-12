/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:54:19 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:06:21 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	safe_free_str(void *ptr)
{
	if (ptr && ptr != (void *)0x1
		&&ptr != (void *)0x2 && ptr != (void *)0x3)
	{
		free(ptr);
	}
}

static void	free_single_cmd_node(t_command_data *cmd)
{
	int	i;

	if (!cmd)
		return ;
	safe_free_str(cmd->cmd_full);
	safe_free_str(cmd->in_file);
	safe_free_str(cmd->out_file);
	safe_free_str(cmd->path_var);
	safe_free_str(cmd->cmd_path);
	if (cmd->cmd_splitted && cmd->cmd_splitted != (char **)0x1
		&& cmd->cmd_splitted != (char **)0x2
		&& cmd->cmd_splitted != (char **)0x3)
		free_2d_arr(cmd->cmd_splitted);
	if (cmd->delim && cmd->delim != (char **)0x1
		&& cmd->delim != (char **)0x2 && cmd->delim != (char **)0x3)
	{
		i = 0;
		while (cmd->delim && cmd->delim[i] != NULL)
		{
			safe_free_str(cmd->delim[i]);
			i++;
		}
		free(cmd->delim);
	}
	free(cmd);
}

void	free_cmds_all(t_command_data **cmds, short count, int start_index)
{
	short	index;

	if (!cmds)
		return ;
	if (start_index < 0)
		start_index = 0;
	index = start_index;
	while (index < count)
	{
		if (cmds[index])
			free_single_cmd_node(cmds[index]);
		index++;
	}
	free(cmds);
}

/*
void	free_cmds_all(t_command_data **cmds, short count, int i)
{
	int	j;

	j = 0;
	while (i > 0 && j < count)
	{
		if (NULL != cmds[i])
		{
			free(cmds[i]->cmd_full);
			free(cmds[i]->in_file);
			free(cmds[i]->out_file);
			free(cmds[i]->delim);
			free(cmds[i]);
		}
		i++;
	}
	free(cmds);
}
*/