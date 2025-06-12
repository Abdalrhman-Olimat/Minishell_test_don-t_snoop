/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_big_malloc_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:54:04 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 04:54:05 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	free_big_malloc_cmds(size_t err_num, t_command_data **cmds, int i)
{
	if (!cmds)
		return ;
	if (i == -1)
	{
		while (cmds[++i])
		{
			if (cmds[i]->cmd_splitted)
				free_2d_arr(cmds[i]->cmd_splitted);
			if (cmds[i]->in_file)
				free(cmds[i]->in_file);
			if (cmds[i]->out_file)
				free(cmds[i]->out_file);
			if (cmds[i]->cmd_full)
				free(cmds[i]->cmd_full);
			if (cmds[i]->cmd_path && !err_num)
				free(cmds[i]->cmd_path);
			if (cmds[i]->delim)
				free_2d_arr(cmds[i]->delim);
			free(cmds[i]);
		}
		free(cmds);
	}
}
