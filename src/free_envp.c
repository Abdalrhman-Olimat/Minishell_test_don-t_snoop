/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:55:01 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:02:13 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	free_envp(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell || !shell->analyzing_data.envp)
		return ;
	while (shell->analyzing_data.envp[i])
	{
		free(shell->analyzing_data.envp[i]);
		i++;
	}
	free(shell->analyzing_data.envp);
	shell->analyzing_data.envp = NULL;
}
