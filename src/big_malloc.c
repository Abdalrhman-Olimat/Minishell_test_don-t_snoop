/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:54:00 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:00:23 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	back_failure(t_shell *shell, int i, int j)
{
	free_cmds_all(shell->cmds, shell->analyzing_data.cmds_count, i);
	return (SHELL_FAILURE);
}

static t_shell_returns	malloc_internals(t_shell *shell, int i, int j)
{
	while (j > 0 && i < shell->analyzing_data.cmds_count)
	{
		prepare_command_struct(shell, i, 1);
		if (j > 0 && shell->cmds[i]->cmd_full == NULL
			|| shell->cmds[i]->in_file == NULL
			|| shell->cmds[i]->out_file == NULL
			|| shell->cmds[i]->delim == NULL)
		{
			return (back_failure(shell, i, j));
		}
		i++;
	}
	return (OK);
}

static t_command_data	**alloc_cmd_array(int count)
{
	t_command_data	**cmds;

	cmds = malloc(sizeof(t_command_data *) * (count + 1));
	if (!cmds)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	return (cmds);
}

static int	alloc_each_cmd(t_command_data **cmds, int count, int i)
{
	while (i < count)
	{
		cmds[i] = malloc(sizeof(t_command_data));
		if (!cmds[i])
		{
			free_cmds_all(cmds, i, 0);
			return (0);
		}
		i++;
	}
	cmds[i] = NULL;
	return (1);
}

t_command_data	**big_malloc(t_shell *shell, int i)
{
	t_command_data	**cmds;

	shell->analyzing_data.cmds_count = count_max_commands(shell, VALID_MLC, 0);
	cmds = alloc_cmd_array(shell->analyzing_data.cmds_count);
	if (!alloc_each_cmd(cmds, shell->analyzing_data.cmds_count, 0))
		return (NULL);
	shell->cmds = cmds;
	if (malloc_internals(shell, 0, 1) != OK)
	{
		free_cmds_all(cmds, shell->analyzing_data.cmds_count, 0);
		return (NULL);
	}
	return (cmds);
}
