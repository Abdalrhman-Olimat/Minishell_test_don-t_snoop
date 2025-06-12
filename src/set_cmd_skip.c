/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_skip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:01:20 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 15:55:40 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	set_status_skip(t_shell *shell, t_command_data **cmd, int *cmd_i,
		int status)
{
	if (FT)
	{
		cmd[*cmd_i]->skip_cmd = true;
		shell->exit_status = status;
	}
}

void	refresh_path_cache(t_shell *sh)
{
	if (sh->analyzing_data.path)
	{
		free_paths_shell(sh);
		sh->analyzing_data.path = NULL;
	}
	if (sh->analyzing_data.envp && sh->analyzing_data.envp[0])
		sh->analyzing_data.path = fetch_path(sh, 0);
	else
		sh->analyzing_data.path = NULL;
}
