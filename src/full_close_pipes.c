/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_close_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:11:12 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:11:13 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	try_to_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	return (0);
}

void	full_close_pipes(t_pipe_data *pipe_data)
{
	int	*fds[5];
	int	i;

	fds[0] = &pipe_data->pipe_fd[0];
	fds[1] = &pipe_data->pipe_fd[1];
	fds[2] = &pipe_data->prev_pipe[0];
	fds[3] = &pipe_data->prev_pipe[1];
	fds[4] = NULL;
	i = 0;
	while (fds[i])
	{
		try_to_close(fds[i]);
		i++;
	}
}
