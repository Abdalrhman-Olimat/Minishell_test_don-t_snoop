/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:53:21 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/11 15:07:04 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	my_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*s1_ptr;
	const unsigned char	*s2_ptr;
	size_t				i;

	if (!s1 || !s2)
	{
		printf("Error: NULL pointer passed to my_strcmp\n");
		return (-1);
	}
	s1_ptr = (const unsigned char *)s1;
	s2_ptr = (const unsigned char *)s2;
	i = 0;
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

int	count_max_commands(t_shell *shell)
{
	int		count;
	int		i;
	bool	expect_command;

	count = 0;
	i = 0;
	expect_command = true;
	if (!shell || !shell->analyzing_data.args)
		return (0);
	while (shell->analyzing_data.args[i])
	{
		if (is_redirection_operator(shell->analyzing_data.args[i]))
		{
			i += 2;
			continue ;
		}
		process_command_token(shell->analyzing_data.args[i],
			&expect_command, &count);
		if (is_pipe_token(shell->analyzing_data.args[i]))
			expect_command = true;
		i++;
	}
	return (count);
}

static bool	process_command_token(const char *token, bool *expect_command,
		int *count)
{
	if (!is_operator(token) && *expect_command)
	{
		(*count)++;
		*expect_command = false;
		return (true);
	}
	return (false);
}

/*

int	count_max_commands(t_shell *shell)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!shell)
		return (0);
	if (!shell->analyzing_data.args)
		return (0);
	while (shell->analyzing_data.args[i])
	{
		if (!is_operator(shell->analyzing_data.args[i]) &&
			(i == 0 || is_operator(shell->analyzing_data.args[i - 1])))
		{
			count++;
		}
		i++;
	}
	shell->analyzing_data.cmds_count = count;
	return (count);
}

// int	count_max_commands(t_shell *shell)
// {
// 	int	count;
// 	int	i;

// 	if (!shell->analyzing_data.args || !shell)
// 		return (0);
// 	count = 0;
// 	i = 0;

// 	// Print arguments for debugging (optional)
// 	// print_args(shell->analyzing_data.args);

// 	while (shell->analyzing_data.args[i])
// 	{
// 		if (my_strcmp(shell->analyzing_data.args[i], "<<") != 0
// 			&& my_strcmp(shell->analyzing_data.args[i], "<") != 0
// 			&& my_strcmp(shell->analyzing_data.args[i], ">>") != 0
// 			&& my_strcmp(shell->analyzing_data.args[i], ">") != 0
// 			&& my_strcmp(shell->analyzing_data.args[i], "|") != 0 && (i == 0
// 				|| (my_strcmp(shell->analyzing_data.args[i - 1], "<<") != 0
// 					&& my_strcmp(shell->analyzing_data.args[i - 1], "<") != 0
// 					&& my_strcmp(shell->analyzing_data.args[i - 1], ">>") != 0
// 					&& my_strcmp(shell->analyzing_data.args[i - 1], ">") != 0)))
// 		{
// 			count++;
// 			shell->analyzing_data.cmds_count++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

void	command_count(t_shell *shell)
{
	int	x;

	if (!shell)
		return ;
	// Get the maximum number of commands
	x = count_max_commands(shell);
	printf("Total valid commands counted: %d\n", x);
	// Allocate memory for the commands array (3D pointer)	
	// Below Was  Working 100% but i will do structures instead of string
	// if (!(x > shell->analyzing_data.pipes_num))
	// 	shell->cmds = malloc(sizeof(char ***) * (shell->analyzing_data.pipes_num
					+ 2));  // +2 for pipes
	// else if (x > shell->analyzing_data.pipes_num)
	// 	shell->cmds = malloc(sizeof(char ***) * (x + 1));  //
			+1 for null terminator
	// if (!shell->cmds)
	// {
	// 	printf("Memory allocation failed for command array\n");
	// 	return ;
	// }
}

void	analyze_cmds(t_shell *shell, int i, int j)
{
	if (!shell)
		return ;
	// Count the number of valid commands
	// print_args(shell->analyzing_data.args);	
	// printf("Total valid commands counted: %d\n", i);	// TEST (3) - Worked
	
	// Below was working 100% but i will do structures instead of string
	// if (!j && i <= shell->analyzing_data.pipes_num)
	// 	shell->cmds = malloc(sizeof(char ***) * (shell->analyzing_data.pipes_num
					+ 2));
	// else
	// 	shell->cmds = malloc(sizeof(char ***) * (i + 1));
}
*/