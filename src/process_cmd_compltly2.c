/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd_compltly2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:46:59 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 13:25:41 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	link_main_cmd(t_shell *sh, int i)
{
	sh->cmds[i]->main_cmd = sh->cmds;
}

int	skip_if_required(t_shell *sh, int i, t_pipe_data *pipes)
{
	if (sh->cmds[i]->skip_cmd)
		return (skip_piped_cmd(sh->cmds[i], pipes));
	return (-1);
}

int	handle_no_pipe_case(t_shell *sh, int i, t_pipe_data *pipes)
{
	int	fdin;
	int	fdout;
	int	ret;

	handle_no_pipes_command(sh->cmds[i], &fdin, &fdout);
	if (is_built_in(sh->cmds[i]))
	{
		ret = exec_builtin(sh, sh->cmds[i], &fdin, &fdout);
		if (ret != -1)
			sh->exit_status = ret;
		restore_io_if_needed(fdin, fdout);
		return (1);
	}
	sh->cmds[i]->content_analyze.stdin_backup = fdin;
	sh->cmds[i]->content_analyze.stdout_backup = fdout;
	return (0);
}
