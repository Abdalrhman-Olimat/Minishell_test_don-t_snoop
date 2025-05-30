/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:43:05 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/30 17:29:33 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
 * Signal handler for interactive mode (prompt)
 * Handles Ctrl+C to display a new prompt
 */
void	sigint_handler(int sig)
{
	extern t_shell *g_shell_ptr; // We'll add this to main.c
	
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	
	// Update the exit status in the shell struct
	if (g_shell_ptr)
		g_shell_ptr->exit_status = 130;
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
 * Setup signal handling for interactive mode (prompt)
 */
void	setup_signals_interactive(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Setup signal handling for command execution mode
 */
void	setup_signals_exec(void)
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigint_handler_child);
}

/*
 * Reset signals to default behavior
 */
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
