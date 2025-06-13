/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmad <ahmad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:27 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 01:35:57 by ahmad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	execute_cmds(t_shell *shell, int i, int j)
{
	t_pipe_data	pipe_data;

	init_execution_data(&pipe_data);
	while (shell->cmds[++i])
	{
		process_cmd_compltly(shell, i, &pipe_data);
	}
	full_close_pipes(&pipe_data);
	// set_all_signals();
	if (pipe_data.got_forked)
		wait_children(shell, shell->cmds, 0, 0);
	return (0);
}
