/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:18:25 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 06:28:15 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	count_tokens(t_input *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

int	fill_token_array(char **array, t_input *head, int i)
{
	char	*trimmed;

	while (head)
	{
		trimmed = ft_strtrim(head->string, " ");
		if (!trimmed)
			return (i);
		array[i] = ft_strdup(trimmed);
		free(trimmed);
		if (!array[i])
			return (i);
		head = head->next;
		i++;
	}
	array[i] = NULL;
	return (-1);
}

void	free_token_array(char **array, int until)
{
	if (!array)
		return ;
	if (until < 0)
		until = 0;
	while (--until >= 0)
	{
		if (array[until] && array[until] != (char *)0x1
			&& array[until] != (char *)0x2 && array[until] != (char *)0x3)
		{
			free(array[until]);
			array[until] = NULL;
		}
	}
	free(array);
}

char	**tokens_to_array(t_input *head)
{
	char	**array;
	int		count;
	int		err;

	count = count_tokens(head);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	err = fill_token_array(array, head, 0);
	if (err >= 0)
	{
		free_token_array(array, err);
		return (NULL);
	}
	return (array);
}
