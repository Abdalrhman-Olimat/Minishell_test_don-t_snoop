/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:59:04 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 10:33:29 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->exit_status = 0;
	shell->tokens = NULL;
	shell->tokens_header = NULL;
	shell->cmds = NULL;
	shell->analyzing_data.args = NULL;
	shell->analyzing_data.cmds_count = 0;
	shell->heredoc_tracker.count = 0;
	shell->heredoc_interrupted = false;
	alloc_envp(shell, envp);
	shell->analyzing_data.path = fetch_path(shell, 0);
	// setup_signals_interactive();
	// setup_signals_prompt();
}

void	reset_shell(t_shell *shell)
{
	if (shell->tokens)
	{
		free_list(shell->tokens);
		shell->tokens = NULL;
	}
	shell->heredoc_interrupted = false;
}

void	free_analyzing_args(t_shell *shell, int count)
{
	if (!shell->analyzing_data.args)
		return ;
	if (count > 0)
		free_token_array(shell->analyzing_data.args, count);
	else
		free(shell->analyzing_data.args);
	shell->analyzing_data.args = NULL;
}

void	cleanup_shell(t_shell *shell)
{
	int	count;

	if (!shell)
		return ;
	count = 0;
	if (shell->tokens)
		count = count_tokens(shell->tokens);
	reset_shell(shell);
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
	free_analyzing_args(shell, count);
	free_both_envp_paths(shell);
}

char	*get_input(void)
{
	char	*input;

	input = readline("minishell> ");
	if (input == NULL)
	{
		printf("exit\n");
		return (NULL);
	}
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}
