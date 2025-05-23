#include "../includes/mini.h"

void exec_with_child(t_shell *shell, t_command_data *command, t_pipe_data *pipe_data, int cmd_iter)
{
	skip_piped_cmd(shell->cmds[cmd_iter], pipe_data);
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
			// else if (/*I think it should check the expanded here ex. : expanded_as_command()... */)
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
		free_cmds_all(command->main_cmd, 127, -1);
		free_both_envp_paths(shell);
		exit(127);
		
		// just_execute(shell, command, 0);
	}
}
