/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_linked_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:31:24 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:31:25 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	normalize_linked_list(t_input *head)
{
	char	*new_str;

	if (!head)
		return ;
	while (head)
	{
		if (head->string && head->string[0] == ' ' && head->string[1] != '\0')
		{
			new_str = ft_strdup(head->string + 1);
			if (new_str)
			{
				free(head->string);
				head->string = new_str;
			}
		}
		else if (head->string && head->string[0] == '\0')
		{
			free(head->string);
			head->string = ft_strdup(" ");
		}
		head = head->next;
	}
}

/*
void	remove_spaces(char *str)
{
	int	i;

    i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
}
*/