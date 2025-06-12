/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_child2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:41:28 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 04:42:48 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	cleanup_and_set_exit_status(t_shell *sh, int code)
{
	free_tracked_heredoc_nodes(&sh->heredoc_tracker);
	free_big_malloc_cmds(0, sh->cmds, -1);
	free_both_envp_paths(sh);
	sh->exit_status = code;
}
