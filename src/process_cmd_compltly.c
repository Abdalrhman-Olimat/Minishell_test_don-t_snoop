/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd_compltly.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:46:55 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:40:24 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static bool	has_pipe_relation(t_shell *sh, int i)
{
	return (sh->cmds[i]->content_analyze.is_there_pipe || (i > 0 && sh->cmds[i
				- 1]->content_analyze.is_there_pipe));
}

void	restore_input_stream(int fd_in)
{
	if (fd_in < 0)
		return ;
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	restore_output_stream(int fd_out)
{
	if (fd_out < 0)
		return ;
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	restore_io_if_needed(int in_fd, int out_fd)
{
	restore_input_stream(in_fd);
	restore_output_stream(out_fd);
}

int	process_cmd_compltly(t_shell *sh, int i, t_pipe_data *pipes)
{
	bool	use_fork;

	link_main_cmd(sh, i);
	use_fork = has_pipe_relation(sh, i);
	if (skip_if_required(sh, i, pipes) != -1)
		return (0);
	if (!use_fork && handle_no_pipe_case(sh, i, pipes))
		return (0);
	exec_with_child(sh, sh->cmds[i], pipes, i);
	switch_pipes(pipes->pipe_fd, pipes->prev_pipe, sh->cmds, i);
	return (0);
}
