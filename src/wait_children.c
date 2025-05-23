#include "../includes/mini.h"

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
