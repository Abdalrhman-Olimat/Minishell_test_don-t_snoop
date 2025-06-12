/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_execution_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:25:32 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:25:35 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	init_execution_data(t_pipe_data *pipe_data)
{
	if (FT)
		pipe_data->got_forked = false;
	pipe_data->pipe_fd[0] = -1;
	if (FT > -1)
		pipe_data->pipe_fd[1] = -1;
	pipe_data->prev_pipe[0] = -1;
	if (FT > 0)
		pipe_data->prev_pipe[1] = -1;
}
