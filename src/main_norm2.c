/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 07:00:06 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 07:01:08 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	process_tokens(t_shell *shell)
{
	if (!shell->tokens)
		return (0);
	if (syntax_checker(shell->tokens) == 0)
	{
		free_list(shell->tokens);
		shell->tokens = NULL;
		return (0);
	}
	return (1);
}

void	init_command_structures(t_shell *shell)
{
	shell->cmds = NULL;
	shell->analyzing_data.args = NULL;
	shell->tokens_header = NULL;
}
