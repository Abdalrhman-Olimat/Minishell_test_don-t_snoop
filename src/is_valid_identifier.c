/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:41:32 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:42:19 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
 * Checks if the character is a valid identifier character (alphanumeric or '_'
 */
int	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_first_char(const char first_char)
{
	return (ft_isalpha(first_char) || first_char == '_');
}

int	is_valid_until_equal_or_end(const char *str, int start_index)
{
	int	i;

	i = start_index;
	while (str[i] && str[i] != '=')
	{
		if (!is_valid_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Checks if the given identifier is valid
 */
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!is_valid_first_char(str[0]))
		return (0);
	i = 1;
	return (is_valid_until_equal_or_end(str, i));
}
