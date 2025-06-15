/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:43:05 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:20:36 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "../includes/mini.h"

static void perform_sigs(struct sigaction sa)
{
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);      
    signal(SIGTSTP, SIG_IGN);      
}

static void signal_handler(int sig)
{
    g_signal = sig;
}

void setup_default_signal(void)
{
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;
    perform_sigs(sa);
}





















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
