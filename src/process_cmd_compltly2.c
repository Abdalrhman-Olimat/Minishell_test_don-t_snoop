#include "../includes/mini.h"

void link_main_cmd(t_shell *sh, int i)
{
	sh->cmds[i]->main_cmd = sh->cmds;
}

int skip_if_required(t_shell *sh, int i, t_pipe_data *pipes)
{
	if (sh->cmds[i]->skip_cmd)
		return (skip_piped_cmd(sh->cmds[i], pipes));
	return (-1);
}

int handle_no_pipe_case(t_shell *sh, int i, t_pipe_data *pipes)
{
	int fdin;
	int fdout;

	handle_no_pipes_command(sh->cmds[i], &fdin, &fdout);
	if (is_built_in(sh->cmds[i]))
	{
		exec_builtin(sh, sh->cmds[i], &fdin, &fdout);
		restore_io_if_needed(fdin, fdout);
		return (1);
	}
	sh->cmds[i]->content_analyze.stdin_backup = fdin;
	sh->cmds[i]->content_analyze.stdout_backup = fdout;
	return (0);
}
