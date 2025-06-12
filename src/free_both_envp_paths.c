/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_both_envp_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:54:08 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 04:54:09 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	free_both_envp_paths(t_shell *shell)
{
	if (shell->analyzing_data.envp)
		free_envp(shell);
	if (shell->analyzing_data.path)
		free_paths_shell(shell);
	return (0);
}
