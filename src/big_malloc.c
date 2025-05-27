#include "../includes/mini.h"

/*
static t_shell_returns init_and_malloc_all(t_shell *shell, int i, int j)
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

static t_shell_returns malloc_internals(t_shell *shell, int i, int j)
{
	while (j > 0 && i < shell->analyzing_data.cmds_count)
	{
		prepare_command_struct(shell, i, 1);
		if (j > 0 && shell->cmds[i]->cmd_full == NULL ||
			shell->cmds[i]->in_file == NULL ||
			shell->cmds[i]->out_file == NULL || 
			shell->cmds[i]->delim == NULL)
		{
			free_cmds_all(shell->cmds, shell->analyzing_data.cmds_count, i);
			return (SHELL_FAILURE);
		}
		i++;
	}
	return (OK);
}

t_command_data **big_malloc(t_shell *shell, int i)
{
	t_command_data **cmds;

	shell->analyzing_data.cmds_count = count_max_commands(shell);
	// printf("shell->analyzing_data.cmds_count = %d\n", shell->analyzing_data.cmds_count);	// TEST (1) : Working 100
	cmds = malloc(sizeof(t_command_data *) * (shell->analyzing_data.cmds_count + 1));
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
