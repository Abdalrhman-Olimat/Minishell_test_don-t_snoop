/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmad <ahmad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:22:51 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 01:18:16 by ahmad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	free_all_and_exit(t_shell *sh, t_command_data *cmd, int code,
		char *msg)
{
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		free(msg);
	}
	if (sh->tokens)
	{
		free_list(sh->tokens);
		sh->tokens = NULL;
	}
	if (sh->tokens_header)
	{
		free_list(sh->tokens_header);
		sh->tokens_header = NULL;
	}
	if (sh->analyzing_data.args)
	{
		free_token_array(sh->analyzing_data.args,
			sh->analyzing_data.cmds_count);
		sh->analyzing_data.args = NULL;
	}
	cleanup_and_set_exit_status(sh, code);
	exit(code);
}

static void	handle_builtin_case(t_shell *sh, t_command_data *cmd)
{
	exec_builtin(sh, cmd, &cmd->content_analyze.stdin_backup,
		&cmd->content_analyze.stdout_backup);
	free_all_and_exit(sh, cmd, 0, NULL);
}

void	handle_path_failure(t_shell *sh, t_command_data *cmd)
{
	char	*err;

	err = ft_strjoin(cmd->cmd_splitted[0], " : No such file or directory\n");
	free_all_and_exit(sh, cmd, 127, err);
}

static void	handle_command_expansion(t_shell *sh, t_command_data *cmd)
{
	if (handle_expansion(sh, cmd) != 0)
	{
		free_and_fetch_pth(sh, cmd);
		handle_failure_of_pth(sh, cmd);
	}
	set_working_cmd(sh, cmd);
}

void	exec_with_child(t_shell *sh, t_command_data *cmd,
		t_pipe_data *pipe_data, int iter)
{
	if (cmd->content_analyze.is_there_pipe)
		if (pipe(pipe_data->pipe_fd) == -1)
			exit_err_str("Pipe failed");
	pipe_data->got_forked = true;
	cmd->p_id = fork();
	if (cmd->p_id == -1)
		exit_err_str("Fork failed");
	if (cmd->p_id == 0)
	{
		g_signal = 0;
		cleanup_child_process(sh);
		exec_child_setting(cmd, pipe_data, iter, 0);
		if (sh && cmd && cmd->cmd_splitted && cmd->cmd_splitted[0])
		{
			if (is_built_in(cmd))
				handle_builtin_case(sh, cmd);
		}
		handle_command_expansion(sh, cmd);
		execve(cmd->cmd_path, cmd->cmd_splitted, sh->analyzing_data.envp);
		free_all_and_exit(sh, cmd, 127, NULL);
	}
}
