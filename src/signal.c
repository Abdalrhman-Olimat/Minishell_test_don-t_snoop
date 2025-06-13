/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmad <ahmad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:43:05 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/13 10:10:12 by ahmad            ###   ########.fr       */
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
	g_cnt_be_interrupted = 130;
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
	write(STDOUT_FILENO, "\n", 1);
}


/*
 * Setup signal handling for command execution mode
 */
void	setup_signals_exec(void)
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigint_handler_child);
}
