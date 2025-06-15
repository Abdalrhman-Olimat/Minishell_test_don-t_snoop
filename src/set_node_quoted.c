/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:00:00 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 05:50:44 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
 * Sets the quoted flag on the last node in the token list
 * Used to track whether a token was enclosed in single or double quotes
 * This affects variable expansion behavior
 */
void	set_node_quoted(t_input **head, bool is_double_quote)
{
	t_input	*current;

	if (!head || !*head)
		return ;
	current = *head;
	while (current->next)
		current = current->next;
	current->flags.is_quoted = true;
}
