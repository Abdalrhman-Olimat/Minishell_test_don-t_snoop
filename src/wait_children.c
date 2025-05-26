#include "../includes/mini.h"

static void	handle_exit_code(t_shell *shell, int code)
{
	if (WIFEXITED(code))
		shell->exit_status = WEXITSTATUS(code);
	else if (WIFSIGNALED(code))
		shell->exit_status = 128 + WTERMSIG(code);
}

static pid_t extract_last_valid_pid(t_command_data **cmds, int index)
{
	pid_t pid;

	pid = -1;
	while (cmds[index])
	{
		if (cmds[index]->p_id > 0)
			pid = cmds[index]->p_id;
		index++;
	}
	return (pid);
}


static void wait_for_main_and_others(t_shell *sh, pid_t last_pid)
{
	int status;
	pid_t temp;

	temp = waitpid(last_pid, &status, 0);
	if (temp == last_pid)
		handle_exit_code(sh, status);
	while (waitpid(-1, &status, 0) > 0)
		;
}

int wait_children(t_shell *shell, t_command_data **cmd_list, int index, pid_t ignored)
{
	pid_t last_pid;

	last_pid = extract_last_valid_pid(cmd_list, 0);
	if (last_pid < 0)
		return (1);
	wait_for_main_and_others(shell, last_pid);
	return (0);
}



/*

#include "../includes/mini.h"

static pid_t extract_last_valid_pid(t_command_data **cmds, int *index)
{
	pid_t latest_pid;

	latest_pid = -1;
	while (cmds[*index])
	{
		if (cmds[*index]->p_id > 0)
			latest_pid = cmds[*index]->p_id;
		(*index)++;
	}
	return (latest_pid);
}

static void wait_and_process_exit_code(t_shell *sh, pid_t target_pid)
{
	int status;
	pid_t waited;

	waited = waitpid(target_pid, &status, 0);
	if (waited == target_pid)
		handle_exit_code(sh, status);

	while ((waited = waitpid(-1, &status, 0)) != -1)
		;
}

int wait_children(t_shell *sh, t_command_data **cmds, int start_index, pid_t placeholder)
{
	pid_t last_pid;

	last_pid = extract_last_valid_pid(cmds, &start_index);
	if (last_pid < 0)
		return (1);
	wait_and_process_exit_code(sh, last_pid);
	return (0);
}


int wait_children(t_shell *shell, t_command_data **commands)
{
	int	status;
	int	i;
	int	last_pid;

	i = 0;
	last_pid = -1;
	while (commands[i])
	{
		if (commands[i]->p_id > 0)
			last_pid = commands[i]->p_id;
		i++;
	}
	if (last_pid == -1)
		return 1;
	if (waitpid(last_pid, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
	}
	while (waitpid(-1, &status, 0) > 0)
		;
}
*/