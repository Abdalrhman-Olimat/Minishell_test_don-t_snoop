/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:25:24 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/14 23:41:58 by aeleimat         ###   ########.fr       */
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

int	ft_echo(char **argv)
{
	int	i;
	int	suppress_newline;
	int	first;

	i = 1;
	suppress_newline = 0;
	first = 1;
	if (argv[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	while (argv[i] != NULL && ft_strcmp(argv[i], "-n") == 0)
	{
		suppress_newline = 1;
		i++;
	}
	while (argv[i] != NULL)
	{
		print_word(argv[i], &first);
		i++;
	}
	if (!suppress_newline)
		printf("\n");
	return (0);
}

/*
int	main(int argc, char *argv[])
{
	// Test cases for ft_echo
	char *test1[] = {"echo", "hello", "world", NULL};
	char *test2[] = {"echo", "-n", "no", "newline", NULL};
	char *test3[] = {"echo", NULL};
	char *test4[] = {"echo", "-n", NULL};
	char *test5[] = {"echo", "-n", "-n", "multiple", "options", NULL};

	printf("Test 1:\n");
	ft_echo(test1);

	printf("Test 2:\n");
	ft_echo(test2);

	printf("Test 3:\n");
	ft_echo(test3);

	printf("Test 4:\n");
	ft_echo(test4);

	printf("Test 5:\n");
	ft_echo(test5);

	return (0);
}*/
