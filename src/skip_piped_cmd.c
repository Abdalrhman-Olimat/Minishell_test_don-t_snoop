/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_piped_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:02:42 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 06:02:43 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	skip_piped_cmd(t_command_data *command, t_pipe_data *pipe_data)
{
	command->p_id = -1;
	if (command->content_analyze.is_there_pipe)
	{
		if (true == command->content_analyze.is_there_pipe)
		{
			if (pipe(pipe_data->pipe_fd) == -1)
				exit_err_str("Pipe failed");
		}
		close(pipe_data->pipe_fd[1]);
		pipe_data->prev_pipe[0] = pipe_data->pipe_fd[0];
		pipe_data->prev_pipe[1] = -1;
	}
	return (0);
}
