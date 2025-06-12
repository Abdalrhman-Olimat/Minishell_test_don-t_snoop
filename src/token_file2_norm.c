/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file2_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:36:59 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 06:37:07 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	fush_token_buffer(t_tokenizer_state *state)
{
	state->token_buf[state->token_index] = '\0';
	append_node(state->head, state->token_buf, TYPE_WORD);
	if (state->quote_char == '\"')
		set_node_quoted(state->head, true);
	state->token_index = 0;
}
