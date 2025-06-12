/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:54:00 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/11 15:12:05 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
static t_shell_returns	init_and_malloc_all(t_shell *shell, int i, int j)
{
	if (shell->cmds[i] && j > 0)
	{
		ft_bzero(shell->cmds[i], sizeof(t_command_data));
		shell->cmds[i]->fd_of_heredoc = -1;
		shell->cmds[i]->cmd_splitted = NULL;
		shell->cmds[i]->cmd_path = NULL;
		shell->cmds[i]->cmd_full = ft_calloc(MAXIMUM_CMD_SIZE, sizeof(char));
		shell->cmds[i]->cmd_full[0] = '\0';
		shell->cmds[i]->in_file = ft_calloc(FILENAME_MAX, sizeof(char));
		shell->cmds[i]->out_file = ft_calloc(FILENAME_MAX, sizeof(char));
		shell->cmds[i]->delim = ft_calloc(4096, sizeof(char));
		if (j < 0 || shell->cmds[i]->delim == NULL ||
			shell->cmds[i]->cmd_full == NULL ||
			shell->cmds[i]->in_file == NULL ||
			shell->cmds[i]->out_file  == NULL)
		{
			if (shell->cmds[i]->cmd_full) 
				free(shell->cmds[i]->cmd_full);
			if (shell->cmds[i]->in_file)
				free(shell->cmds[i]->in_file);
			if (shell->cmds[i]->out_file)
				free(shell->cmds[i]->out_file);
			if (shell->cmds[i]->delim)
				free(shell->cmds[i]->delim);
			return (SHELL_FAILURE);
		}
		return (SHELL_SUCCESS);
	}
}
*/
static int back_failure(t_shell *shell, int i, int j)
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

	shell->analyzing_data.cmds_count = count_max_commands(shell);
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

/*
t_command_data	**big_malloc(t_shell *shell, int i)
{
	t_command_data	**cmds;

	shell->analyzing_data.cmds_count = count_max_commands(shell);
	// printf("shell->analyzing_data.cmds_count = %d\n",
				shell->analyzing_data.cmds_count);	// TEST (1) : Working 100
	cmds = malloc(sizeof(t_command_data *) * (shell->analyzing_data.cmds_count
				+ 1));
	if (!cmds)
	{
		perror("Memory allocation failed");
		// TODO: free all allocated memory
			// free_list(shell->tokens);
			// free_envp(shell);
			// free(shell->analyzing_data.args);
			// free(shell->analyzing_data.path);
			// free(shell->analyzing_data.envp);
		exit(1);
	}
	i = 0;
	while (i < shell->analyzing_data.cmds_count)
	{
		cmds[i] = malloc(sizeof(t_command_data));
		if (NULL == cmds[i])
		{
			free_cmds_all(cmds, i, 0);
			return (NULL);
		}
		i++;
	}
	cmds[i] = NULL;
	shell->cmds = cmds;
	if (malloc_internals(shell, 0, 1) != OK)
	{
		free_cmds_all(cmds, shell->analyzing_data.cmds_count, 0);
		return (NULL);
	}
	return (cmds);
}
*/
