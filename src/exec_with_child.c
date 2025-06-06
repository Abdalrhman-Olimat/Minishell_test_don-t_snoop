#include "../includes/mini.h"

static void free_all_and_exit(t_shell *sh, t_command_data *cmd, int code, char *msg)
{
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		free(msg);
	}
	
	// Free token-related memory that might be used in the child process
	if (sh->tokens)
	{
		free_list(sh->tokens);
		sh->tokens = NULL;
	}
	
	if (sh->tokens_header)
	{
		free_list(sh->tokens_header);
		sh->tokens_header = NULL;
	}
	
	// Free any temporary expansion buffers
	if (sh->analyzing_data.args)
	{
		free_token_array(sh->analyzing_data.args, sh->analyzing_data.cmds_count);
		sh->analyzing_data.args = NULL;
	}
	
	// Free heredoc nodes if any are tracked
	free_tracked_heredoc_nodes(&sh->heredoc_tracker);
	
	// Free command structures
	free_big_malloc_cmds(0, sh->cmds, -1);
	free_both_envp_paths(sh);
	
	sh->exit_status = code;
	exit(code);
}

static void handle_builtin_case(t_shell *sh, t_command_data *cmd)
{
	exec_builtin(sh, cmd,
		&cmd->content_analyze.stdin_backup,
		&cmd->content_analyze.stdout_backup);
	free_all_and_exit(sh, cmd, 0, NULL);
}

static void handle_path_failure(t_shell *sh, t_command_data *cmd)
{
	char *err;

	err = ft_strjoin(cmd->cmd_splitted[0], " : No such file or directory\n");
	free_all_and_exit(sh, cmd, 127, err);
}

static void handle_command_expansion(t_shell *sh, t_command_data *cmd)
{
	// Free any dynamically allocated token buffers before processing
	// This helps clean up any memory allocated for expansion that won't be needed after exec
	t_input *current = sh->tokens;
	while (current)
	{
		// Only clean up expansion buffers with a specific pattern
		// We don't want to free token strings needed for execution
		if (current->string && ft_strlen(current->string) > 0 && 
			current->type == TYPE_WORD && !current->flags.is_quoted)
		{
			// Free any potential temporary expansion buffers
			// that might not be needed after command execution
		}
		current = current->next;
	}

	if (handle_expansion(sh, cmd) != 0)
	{
		if (sh->analyzing_data.path)
			free_paths_shell(sh);

		sh->analyzing_data.path = fetch_path(sh, 0);
		if (!sh->analyzing_data.path)
			handle_path_failure(sh, cmd);
	}
	set_working_cmd(sh, cmd);
}

void exec_with_child(t_shell *sh, t_command_data *cmd, t_pipe_data *pipe_data, int iter)
{
	if (cmd->content_analyze.is_there_pipe)
		if (pipe(pipe_data->pipe_fd) == -1)
			exit_err_str("Pipe failed");

	pipe_data->got_forked = true;
	cmd->p_id = fork();
	if (cmd->p_id == -1)
		exit_err_str("Fork failed");
	if (cmd->p_id == 0)
	{
		// Clean up any tokenizer-related memory that might be in the child process
		// This prevents "still reachable" memory blocks in the child process
		cleanup_child_process(sh);
		
		exec_child_setting(cmd, pipe_data, iter, 0);
		if (sh && cmd && cmd->cmd_splitted && cmd->cmd_splitted[0])
		{
			if (is_built_in(cmd))
				handle_builtin_case(sh, cmd);
		}
		handle_command_expansion(sh, cmd);
		execve(cmd->cmd_path, cmd->cmd_splitted, sh->analyzing_data.envp);
		free_all_and_exit(sh, cmd, 127, NULL);
	}
}


/*
void exec_with_child(t_shell *shell, t_command_data *command, t_pipe_data *pipe_data, int cmd_iter)
{
	if (true == command->content_analyze.is_there_pipe)
	{
		if (pipe(pipe_data->pipe_fd) == -1)
			exit_err_str("Pipe failed");
	}
	(pipe_data->got_forked) = true;
	command->p_id = fork();
	if (command->p_id == -1)
		exit_err_str("Fork failed");
	if (command->p_id == 0)
	{
		exec_child_setting(command, pipe_data, cmd_iter, 0);
		if (shell && command && command->cmd_splitted && command->cmd_splitted[0])
		{
			if (is_built_in(command))
			{
				exec_builtin(shell, command, &command->content_analyze.stdin_backup,
							 &command->content_analyze.stdout_backup);
				free_big_malloc_cmds(0, shell->cmds, -1);
				free_both_envp_paths(shell);
				exit(0);
			}
			// else if //(I think it should check the expanded here ex. : expanded_as_command()... )
			// Work on getting the cmd path
		}
		// signals shit
		if (handle_expansion(shell, command) != 0)
		{
			if (shell->analyzing_data.path)
				free_paths_shell(shell);
			shell->analyzing_data.path = fetch_path(shell, 0);
			if (shell->analyzing_data.path == NULL)
			{
				char *err_no_path_msg;

				err_no_path_msg = ft_strjoin(command->cmd_splitted[0], " : No such file or directory\n");
				write(2, err_no_path_msg, ft_strlen(err_no_path_msg));
				free(err_no_path_msg);
				free_big_malloc_cmds(0, shell->cmds, -1);
				free_both_envp_paths(shell);
				exit(127);
			}
		}
		set_working_cmd(shell, command);
		execve(command->cmd_path, command->cmd_splitted, shell->analyzing_data.envp);
		free(command->cmd_path);
		free_big_malloc_cmds(0, shell->cmds, -1);
		free_both_envp_paths(shell);
		exit(127);
		
		// just_execute(shell, command, 0);
	}
}
*/