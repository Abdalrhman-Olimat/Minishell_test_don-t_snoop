#include "../includes/mini.h"

static void	handle_exit_code(t_shell *shell, int code)
{
	if (WIFEXITED(code))
		shell->exit_status = WEXITSTATUS(code);
	else if (WIFSIGNALED(code))
		shell->exit_status = 128 + WTERMSIG(code);
}

/*
	waited and i are general variables i cant put because number of lines is limited so i send by pars
*/
int wait_children(t_shell *shell, t_command_data **cmd_list, int i, pid_t waited)
{
	int		status;
	pid_t	last_pid;

	last_pid = -1;
	while (cmd_list[i])
	{
		if (cmd_list[i]->p_id > 0)
			last_pid = cmd_list[i]->p_id;
		i++;
	}
	if (last_pid < 0)
		return (1);
	waited = waitpid(last_pid, &status, 0);
	if (waited == last_pid)
		handle_exit_code(shell, status);
	waited = 0;
	while (waited != -1)
		waited = waitpid(-1, &status, 0);
	return (0);
}

/*
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