/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:24:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 19:52:41 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

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
	//print_tokens(shell->tokens);//printing for debug
	execute_commands(shell);
	if (shell->heredoc_interrupted)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
	cleanup_after_execution(shell);
	reset_shell(shell);
	return (1);
}

void	mini_loop(t_shell *shell)
{
	char	*input;
	
	g_signal = 0;
	while (1)
	{
		setup_prompt_signal();
		input = get_input();
		setup_default_signal();
		if (g_signal == SIGINT)
		{
			shell->exit_status = 130;
			g_signal = 0;
		}
		if (!input)
			break ;
		process_input_line(shell, input);
		free(input);
		if (shell->tokens)
		{
			free_list(shell->tokens);
			shell->tokens = NULL;
		}
	}
	reset_shell(shell);
	clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp);
	mini_loop(&shell);
	cleanup_shell(&shell);
	free_tracked_heredoc_nodes(&shell.heredoc_tracker);
	return (shell.exit_status);
}
