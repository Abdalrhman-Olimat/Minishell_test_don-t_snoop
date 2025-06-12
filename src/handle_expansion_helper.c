/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:11:30 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:11:31 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	was_expansion_needed(t_command_data *cmd)
{
	if (cmd->was_quoted == 1)
		return (0);
	if (!ft_strchr(cmd->cmd_splitted[0], ' '))
		return (0);
	return (1);
}

char	**split_primary_argument(t_command_data *cmd)
{
	char	**tokens;

	tokens = ft_split(cmd->cmd_splitted[0], ' ');
	return (tokens);
}

int	add_remaining_arguments(char ***base, char **original)
{
	if (original[1] != NULL)
	{
		if (!append_args_safely(base, original, 1))
			return (0);
	}
	return (1);
}

void	update_command_and_path(t_shell *shell, t_command_data *cmd,
		char **new_tokens)
{
	free_2d_arr(cmd->cmd_splitted);
	cmd->cmd_splitted = new_tokens;
	set_working_cmd(shell, cmd);
}
