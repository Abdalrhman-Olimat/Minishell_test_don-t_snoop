/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:04:46 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 06:39:28 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	my_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*s1_ptr;
	const unsigned char	*s2_ptr;
	size_t				i;

	i = 0;
	s1_ptr = (const unsigned char *)s1;
	s2_ptr = (const unsigned char *)s2;
	if (!s1 || !s2)
	{
		printf("Error: NULL pointer passed to my_strcmp\n");
		return (-1);
	}
	while (s1_ptr[i] == s2_ptr[i] && s1_ptr[i])
		i++;
	return (s1_ptr[i] - s2_ptr[i]);
}

int	is_operator(const char *arg)
{
	if (!arg)
		return (0);
	if (matches_redirection(arg))
		return (1);
	if (matches_double_redirection(arg))
		return (1);
	if (is_pipe_token(arg))
		return (1);
	return (0);
}

bool	is_redirection_operator(char *arg)
{
	return (arg && (ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0
			|| ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0));
}

static int	process_token22(t_shell *shell, int *i, int *count,
		bool *expect_command)
{
	if (is_redirection_operator(shell->analyzing_data.args[*i]))
	{
		*i += 2;
		return (1);
	}
	if (!is_operator(shell->analyzing_data.args[*i]) && *expect_command)
	{
		(*count)++;
		*expect_command = false;
		return (1);
	}
	return (0);
}

int	count_max_commands(t_shell *shell, int go_default, int i)
{
	int		count;
	bool	expect_command;

	if(go_default > 1)
		expect_command = true;
	if (go_default > FT)
		count = 0;
	if (!shell || !shell->analyzing_data.args)
		return (0);
	while (shell->analyzing_data.args[i])
	{
		if (process_token22(shell, &i, &count, &expect_command))
			continue ;
		else if (is_pipe_token(shell->analyzing_data.args[i]))
			expect_command = true;
		i++;
	}
	return (count);
}
