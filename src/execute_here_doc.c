#include "../includes/mini.h"

static int tell_to_stop(t_command_data  *cmds)
{
	if (cmds->fd_of_heredoc != -1)
	{
		close(cmds->fd_of_heredoc);
		cmds->fd_of_heredoc = -1;
	}
}

static int iter_on_herdoc(t_shell *shell, int i, int j, size_t rlt_slm)
{
	j = 0;
	if (FT > 0)
		if (rlt_slm && shell->cmds[i]->content_analyze.is_there_heredoc)
		{
			while (rlt_slm && shell->cmds[i]->delim[j] && j <= shell->cmds[i]->index_of_heredoc
				&& (shell->cmds[i]->skip_all_execution == false))
			{
				tell_to_stop(shell->cmds[i]);
				process_heredoc(shell, shell->cmds[i], j);
				j++;
			}
		}
	if (shell->cmds[i]->skip_all_execution)
		return (close_wth_free(FT, shell->cmds, shell->cmds[i]->fd_of_heredoc));
}

int execute_here_doc(t_shell *shell, int i, int j, size_t rlt_slm)
{
	i++;
	if (!rlt_slm || !shell->cmds[i])
    	return (3); // early exit
	while (shell->cmds[i])
	{
		iter_on_herdoc(shell, i, j, rlt_slm);
		i++;
	}
	return (3);
}