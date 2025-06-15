/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:47:24 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:37:52 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

size_t	count_tokens_till_pipe(t_input *current_token)
{
	size_t	count;

	count = 0;
	while (current_token && current_token->type != TYPE_PIPE)
	{
		count++;
		current_token = current_token->next;
	}
	return (count);
}

int	process_token_word(size_t *splt_arg_index, t_shell *shell,
		t_input *current_token, t_command_data *cmds)
{
	if (current_token->string[0] != '\0')
	{
		if (*splt_arg_index == 0)
		{
			if (cmds->cmd_splitted == NULL)
				cmds->cmd_splitted = ft_calloc((1
							+ count_tokens_till_pipe(current_token)),
						sizeof(char *));
			cmds->cmd_splitted[*splt_arg_index]
				= ft_strdup(current_token->string);
			(*splt_arg_index)++;
		}
		else
		{
			cmds->cmd_splitted[*splt_arg_index]
				= ft_strdup(current_token->string);
			(*splt_arg_index)++;
		}
		process_cmd_quoted_error(shell, cmds);
	}
	return (1);
}
