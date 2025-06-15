/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:18:34 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:23:04 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	handle_exit_code(t_shell *shell, int code)
{
	if (WIFEXITED(code))
		shell->exit_status = WEXITSTATUS(code);
	else if (WIFSIGNALED(code))
		shell->exit_status = 128 + WTERMSIG(code);
}

static pid_t	extract_last_valid_pid(t_command_data **cmds, int index)
{
	pid_t	pid;

	pid = -1;
	while (cmds[index])
	{
		if (cmds[index]->p_id > 0)
			pid = cmds[index]->p_id;
		index++;
	}
	return (pid);
}

static void	wait_for_main_and_others(t_shell *sh, pid_t last_pid)
{
	int		status;
	pid_t	temp;

	temp = waitpid(last_pid, &status, 0);
	if (temp == last_pid)
		handle_exit_code(sh, status);
	while (waitpid(-1, &status, 0) > 0)
		;
}

int	wait_children(t_shell *shell, t_command_data **cmd_list, int index,
		pid_t ignored)
{
	pid_t	last_pid;

	last_pid = extract_last_valid_pid(cmd_list, 0);
	if (last_pid < 0)
		return (1);
	wait_for_main_and_others(shell, last_pid);
	return (0);
}
