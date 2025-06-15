/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:30:46 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:35:08 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

t_input	*create_node(char *str, int type)
/*
 * Creates a new token node with the given string and type
 * Returns the created node or NULL on allocation failure
 */
{
	t_input	*new_node;

	new_node = malloc(sizeof(t_input));
	if (!new_node)
		return (NULL);
	new_node->string = ft_strdup(str);
	if (!new_node->string)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_input **head, char *str, int type)
/*
 * Appends a new token node to the end of the linked list
 * Exits program on memory allocation failure
 */
{
	t_input	*new_node;
	t_input	*tmp;

	new_node = create_node(str, type);
	if (!new_node)
	{
		write(2, "Memory allocation failed\n", 26);
		exit(EXIT_FAILURE);
	}
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	free_list(t_input *head)
/*
 * Frees all memory associated with a linked list of tokens
 * Recursively traverses the list freeing each node and its contents
 */
{
	t_input	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->string);
		free(tmp);
	}
}

void	print_tokens(t_input *head)
/*
 * Debugging function that prints all tokens in the list
 * Shows the token string and type for each node
 */
{
	t_input	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("Token: [%s], Type: [%d]\n", tmp->string, tmp->type);
		tmp = tmp->next;
	}
}

int	malloc_error1(void)
{
	write(2, "Error: Memory allocation failed\n", 32);
	return (0);
}
