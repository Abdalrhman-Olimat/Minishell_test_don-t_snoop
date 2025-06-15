/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:18:42 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:23:13 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	words_to_cmd(t_shell *shell, t_input *token, t_command_data **cmd,
		int *cmd_i)
{
	if (cmd[*cmd_i]->cmd_full[0] == '\0')
	{
		ft_strlcpy(cmd[*cmd_i]->cmd_full, token->string, MAXIMUM_CMD_SIZE);
	}
	else
	{
		ft_strlcat(cmd[*cmd_i]->cmd_full, " ", MAXIMUM_CMD_SIZE);
		ft_strlcat(cmd[*cmd_i]->cmd_full, token->string, MAXIMUM_CMD_SIZE);
	}
	return (0);
}
