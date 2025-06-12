/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:24:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 07:00:37 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/* Global pointer to shell struct for signal handlers */
t_shell		*g_shell_ptr = NULL;

void	execute_commands(t_shell *shell)
{
	expand_tokens(shell);
	play_after_tokens(shell);
}

void	cleanup_after_execution(t_shell *shell)
{
	int	count;

	if (shell->tokens_header)
	{
		free_list(shell->tokens_header);
		shell->tokens_header = NULL;
	}
	if (shell->cmds && shell->analyzing_data.cmds_count > 0)
	{
		free_cmds_all(shell->cmds, shell->analyzing_data.cmds_count, 0);
		shell->cmds = NULL;
	}
	if (shell->analyzing_data.args)
	{
		if (shell->tokens)
		{
			count = count_tokens(shell->tokens);
			free_token_array(shell->analyzing_data.args, count);
		}
		else
			free(shell->analyzing_data.args);
		shell->analyzing_data.args = NULL;
	}
	free_tracked_heredoc_nodes(&shell->heredoc_tracker);
	shell->heredoc_tracker.count = 0;
}

static int	process_input_line(t_shell *shell, char *input)
{
	int	len;

	len = ft_strlen(input);
	if (len == 0)
		return (1);
	shell->heredoc_tracker.count = 0;
	shell->tokens = tokenizer(shell, input, len);
	if (!process_tokens(shell))
		return (1);
	init_command_structures(shell);
	execute_commands(shell);
	cleanup_after_execution(shell);
	setup_signals_exec();
	setup_signals_interactive();
	reset_shell(shell);
	return (1);
}

void	mini_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		setup_signals_interactive();
		input = get_input();
		if (!input)
			break ;
		process_input_line(shell, input);
		free(input);
	}
	reset_shell(shell);
	clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	g_shell_ptr = &shell;
	mini_loop(&shell);
	cleanup_shell(&shell);
	free_tracked_heredoc_nodes(&shell.heredoc_tracker);
	return (shell.exit_status);
}
