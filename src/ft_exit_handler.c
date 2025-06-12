/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:55:53 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 04:55:54 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
 * Handle the exit from the shell
 * 
 * shell: The shell structure to clean up
 * message: Custom message to display (optional)
 * error_msgs: Array of error messages to display (optional)
 * exit_code: The exit status to use
 */
void	ft_exit_handler(t_shell *shell, char *message, char **error_msgs,
		int exit_code)
{
	int	i;

	if (shell)
		shell->exit_status = exit_code;
	if (message)
		ft_putendl_fd(message, 1);
	if (error_msgs)
	{
		i = 0;
		while (error_msgs[i])
		{
			ft_putstr_fd(error_msgs[i], 2);
			i++;
		}
	}
	cleanup_shell(shell);
	rl_clear_history();
	exit(exit_code);
}
