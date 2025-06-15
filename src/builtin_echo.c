/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:25:24 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:32:30 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	print_word(char *word, int *first_ptr)
{
	if (!*first_ptr)
		printf(" ");
	printf("%s", word);
	*first_ptr = 0;
}

static int	parse_echo_flags(char **argv, int *suppress_newline)
{
	int	i;
	int	j;

	i = 1;
	*suppress_newline = 0;
	while (argv[i] != NULL && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		*suppress_newline = 1;
		i++;
	}
	return (i);
}

int	ft_echo(char **argv)
{
	int	i;
	int	suppress_newline;
	int	first;

	first = 1;
	if (argv[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	i = parse_echo_flags(argv, &suppress_newline);
	while (argv[i] != NULL)
	{
		print_word(argv[i], &first);
		i++;
	}
	if (!suppress_newline)
		printf("\n");
	return (0);
}
