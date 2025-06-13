/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmad <ahmad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:43:05 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 01:06:15 by ahmad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"






















// void	sigint_handler(int sig)
// {
// 	if (sig == SIGINT || sig == SIGQUIT)
// 		g_signal = sig;
// }

// void	setup_signals_prompt(void)
// {
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	setup_signals_exec(void)
// {
// 	signal(SIGINT, sigint_handler_exec);
// 	signal(SIGQUIT, sigint_handler_exec);
// }


// // /*
// //  * Setup signal handling for interactive mode (prompt)
// //  */
// void	setup_signals_interactive(void)
// {
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void flush_stdin_buffer(void)
// {
// 	int	fd = open("/dev/tty", O_RDONLY);
// 	if (fd >= 0)
// 	{
// 		ioctl(fd, TCFLSH, 0);
// 		close(fd);
// 	}
// }

// // /*
// //  * Signal handler for interactive mode (prompt)
// //  * Handles Ctrl+C to display a new prompt
// //  */
// void	sigint_handler(int sig)
// {
// 	if (sig == SIGINT || sig == SIGQUIT)
// 		g_signal = sig;
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	g_signal = 130;
	
// }

// void	sigint_handler_exec(int sig)
// {
// 	if (sig == SIGINT || sig == SIGQUIT)
// 		g_signal = sig;
// 	(void)sig;
// 	flush_stdin_buffer();
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	g_signal = 130;
// }

// // /*
// //  * Reset signals to default behavior
// //  */
// void	reset_signals(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

// /*
//  * Signal handler for child processes
//  * Simply forwards the signal to the process
//  */
// void	sigint_handler_child(int sig)
// {
// 	(void)sig;
// 	write(STDOUT_FILENO, "\n", 1);
// }


// /*
//  * Setup signal handling for command execution mode
//  */
// void	setup_signals_exec(void)
// {
// 	signal(SIGINT, sigint_handler_child);
// 	signal(SIGQUIT, sigint_handler_child);
// }
