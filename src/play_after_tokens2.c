/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_after_tokens2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:58:10 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:58:20 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

t_input	*create_token_node_copy(t_input *current_node)
{
	t_input	*new_node;

	new_node = (t_input *)malloc(sizeof(t_input));
	if (new_node == NULL)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_input));
	if (current_node->string != NULL)
	{
		new_node->string = ft_strdup(current_node->string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->string = NULL;
	new_node->type = current_node->type;
	new_node->flags = current_node->flags;
	new_node->next = NULL;
	return (new_node);
}

bool	initialize_token_copy(t_shell *shell, t_input *head,
		t_input **new_tokens, t_input **last_new)
{
	if (shell == NULL || head == NULL)
		return (false);
	*new_tokens = NULL;
	*last_new = NULL;
	return (true);
}
