/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_both_envp_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:54:08 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 15:37:00 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	free_both_envp_paths(t_shell *shell)
{
	if (shell && shell->analyzing_data.path)
	{
		free_paths_shell(shell);
		shell->analyzing_data.path = NULL;
	}
	if (shell && shell->analyzing_data.envp)
	{
		free_envp(shell);
		shell->analyzing_data.envp = NULL;
	}
	return (0);
}
