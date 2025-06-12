/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:49:19 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 03:49:21 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	process_exit_arg(t_shell *shell, char *arg)
{
	int	exit_code;

	if (ft_isnumber(arg))
	{
		exit_code = ft_atoi(arg) % 256;
		shell->exit_status = exit_code;
		ft_exit_handler(shell, NULL, NULL, exit_code);
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit_code = 2;
		shell->exit_status = exit_code;
		ft_exit_handler(shell, NULL, NULL, exit_code);
	}
}

int	ft_exit(char **args, t_shell *shell)
{
	int	exit_code;

	ft_putendl_fd("exit", 1);
	if (args[1] && args[2])
	{
		if (ft_isnumber(args[1]))
		{
			ft_putendl_fd("exit: too many arguments", 2);
			shell->exit_status = 1;
			return (1);
		}
	}
	if (args[1])
	{
		process_exit_arg(shell, args[1]);
	}
	exit_code = shell->exit_status;
	ft_exit_handler(shell, NULL, NULL, exit_code);
	return (0);
}
