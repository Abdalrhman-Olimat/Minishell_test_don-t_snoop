/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds_frst_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:45:58 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:45:59 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	print_cmds_frst_arg(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmds[i])
	{
		if (shell->cmds[i]->cmd_splitted && shell->cmds[i]->cmd_splitted[0])
		{
			printf("Command %d: %s\n", i, shell->cmds[i]->cmd_splitted[0]);
		}
		else
		{
			printf("Command %d: No arguments found\n", i);
		}
		i++;
	}
}
