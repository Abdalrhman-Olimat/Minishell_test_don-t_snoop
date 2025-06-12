/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:43:05 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 18:08:02 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
 * Setup signal handling for interactive mode (prompt)
 */
void	setup_signals_interactive(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Signal handler for interactive mode (prompt)
 * Handles Ctrl+C to display a new prompt
 */
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_cnt_be_interrupted = 130; /* Use the global variable to indicate SIGINT */
}

/*
 * Reset signals to default behavior
 */
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
 * Signal handler for child processes
 * Simply forwards the signal to the process
 */
void	sigint_handler_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

/*
 * Setup signal handling for command execution mode
 */
void	setup_signals_exec(void)
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigint_handler_child);
}
