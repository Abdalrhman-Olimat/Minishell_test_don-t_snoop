/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:45:46 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 15:59:10 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	initialize_null_fields(t_command_data *cmd)
{
	cmd->fd_of_heredoc = -1;
	cmd->cmd_splitted = NULL;
	cmd->cmd_path = NULL;
	cmd->cmd_full = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->delim = NULL;
}

static void	callc_all(t_command_data *cmd, int which)
{
	if (which == CLC_IN_F)
		cmd->in_file = ft_calloc(FILENAME_MAX, sizeof(char));
	else if (which == CLC_OUT_F)
		cmd->out_file = ft_calloc(FILENAME_MAX, sizeof(char));
	else if (which == CLC_CMD_FULL)
		cmd->cmd_full = ft_calloc(MAXIMUM_CMD_SIZE, sizeof(char));
	else if (which == CLC_DELM)
		cmd->delim = ft_calloc(10, sizeof(char *));
}

static int	allocate_fields(t_command_data *cmd)
{
	callc_all(cmd, CLC_CMD_FULL);
	callc_all(cmd, CLC_IN_F);
	callc_all(cmd, CLC_OUT_F);
	callc_all(cmd, CLC_DELM);
	if (!cmd->cmd_full || !cmd->in_file || !cmd->out_file || !cmd->delim)
		return (0);
	cmd->cmd_full[0] = '\0';
	return (1);
}

static void	free_partial_allocs(t_command_data *cmd)
{
	if (cmd->cmd_full)
		free(cmd->cmd_full);
	if (cmd->in_file)
		free(cmd->in_file);
	if (cmd->out_file)
		free(cmd->out_file);
	if (cmd->delim)
		free(cmd->delim);
}

t_shell_returns	prepare_command_struct(t_shell *shell, int i, int j)
{
	t_command_data	*cmd;

	if (!shell->cmds[i] || j <= 0)
		return (SHELL_FAILURE);
	cmd = shell->cmds[i];
	ft_bzero(cmd, sizeof(t_command_data));
	initialize_null_fields(cmd);
	if (!allocate_fields(cmd))
	{
		free_partial_allocs(cmd);
		return (SHELL_FAILURE);
	}
	return (SHELL_SUCCESS);
}
