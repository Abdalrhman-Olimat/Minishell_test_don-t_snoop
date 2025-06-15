/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:11:39 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:10:14 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	**realloc_2d_appending(char **old, int old_size, int new_size)
{
	char	**new_arr;
	int		i;

	new_arr = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_arr[i] = old[i];
		i++;
	}
	while (i < new_size)
	{
		new_arr[i] = NULL;
		i++;
	}
	new_arr[new_size] = NULL;
	free(old);
	return (new_arr);
}

int	append_args_safely(char ***args_ref, char **suffix, int skip)
{
	int	start_index;

	start_index = get_2d_len(*args_ref);
	*args_ref = allocate_expanded_args(*args_ref, suffix, skip);
	if (!*args_ref)
		return (0);
	return (copy_suffix(*args_ref, suffix, start_index, skip));
}

int	handle_expansion(t_shell *shell, t_command_data *cmd)
{
	char	**tokens;

	if (!was_expansion_needed(cmd))
		return (0);
	tokens = split_primary_argument(cmd);
	if (tokens == NULL)
		return (1);
	if (!add_remaining_arguments(&tokens, cmd->cmd_splitted))
	{
		free_2d_arr(tokens);
		return (2);
	}
	update_command_and_path(shell, cmd, tokens);
	return (0);
}
