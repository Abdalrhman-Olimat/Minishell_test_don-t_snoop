/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmds_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:07:51 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 04:07:52 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	count_and_skip(t_input **cursor, size_t *word_count)
{
	while (*cursor && (*cursor)->type != TYPE_PIPE)
	{
		if ((*cursor)->type == TYPE_WORD)
			(*word_count)++;
		*cursor = (*cursor)->next;
	}
	return (0);
}

size_t	count_cmds_tokens(t_input *start_token)
{
	size_t	count;

	count = 0;
	count_and_skip(&start_token, &count);
	return (count);
}

/*
size_t	count_cmds_tokens(t_input *current_token)
{
	size_t	tokens_count;

	tokens_count = 0;
	while (current_token && current_token->type != TYPE_PIPE)
	{
		if (current_token->type == TYPE_WORD)
			tokens_count++;
		current_token = current_token->next;
	}
	return (tokens_count);
}
*/