/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:26:39 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:43:19 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	check_match(char *input, const char *builtin)
{
	return (ft_strncmp(input, builtin, 8) == 0);
}

int	loop_on_all_built_ins(const char *name, const char *built_in_commands[],
		int i)
{
	while (built_in_commands[++i])
	{
		if (check_match((char *)name, built_in_commands[i]))
			return (1);
	}
	return (0);
}

int	is_built_in(t_command_data *command)
{
	char				*name;
	static const char	*built_in_commands[] = {
		"cd",
		"echo",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL};

	if (!command || !command->cmd_splitted || !command->cmd_splitted[0])
		return (0);
	name = command->cmd_splitted[0];
	return (loop_on_all_built_ins(name, built_in_commands, -1));
}
