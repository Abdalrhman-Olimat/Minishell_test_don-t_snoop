/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:30:46 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/28 22:40:57 by aeleimat         ###   ########.fr       */
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
	new_node->flags.is_quoted = false;  // Initialize the flag to false by default
	return (new_node);
}

void	append_node(t_input **head, char *str, int type)
{
    t_input	*new_node;
    t_input	*tmp;

    // First make sure head is valid
    if (!head)
    {
        write(2, "Invalid head pointer\n", 21);
        return;
    }
    
    new_node = create_node(str, type);
    if (!new_node)
    {
        write(2, "Memory allocation failed\n", 26);
        exit(EXIT_FAILURE);
    }
    
    // Safely add the node to the list
    if (!*head)
    {
        *head = new_node;
        return;
    }
    
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void	set_node_quoted(t_input **head, bool is_quoted)
{
    t_input	*tmp;

    if (!*head)
        return;
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->flags.is_quoted = is_quoted;
}

void	free_list(t_input *head)
/*
 * Frees all memory associated with a linked list of tokens
 * Traverses the list freeing each node and its contents
 */
{
	t_input	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->string)
			free(tmp->string);
		free(tmp);
	}
}

void	print_tokens(t_input *head)
/*
 * Debugging function that prints all tokens in the list
 * Shows the token string, type, and quoted status for each node
 */
{
    t_input	*tmp;

    tmp = head;
    while (tmp)
    {
        printf("Token: [%s], Type: [%d], Quoted: [%s]\n", 
            tmp->string, 
            tmp->type, 
            tmp->flags.is_quoted ? "true" : "false");
        tmp = tmp->next;
    }
}
