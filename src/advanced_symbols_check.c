/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_symbols_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:53:02 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/11 14:53:03 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	advanced_symbols_check(t_shell *shell, t_input **tokens,
		int *itereator_of_cmd)
{
	if (!(*tokens)->next || (*tokens)->next->type != TYPE_WORD)
	{
		shell->cmds[*itereator_of_cmd]->skip_cmd = true;
		shell->exit_status = 2;
	}
	else
		shell->cmds[*itereator_of_cmd]->skip_cmd = false;
}
