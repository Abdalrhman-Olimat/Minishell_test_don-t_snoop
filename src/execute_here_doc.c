#include "../includes/mini.h"

int execute_here_doc(t_shell *shell, int i, int j, size_t rlt_slm)
{
	while (rlt_slm && shell->cmds[++i])
	{
		j = 0;
		if (rlt_slm && shell->cmds[i]->content_analyze.is_there_heredoc)
		{
			while (rlt_slm && shell->cmds[i]->delim[j] && j <= shell->cmds[i]->index_of_heredoc
				&& (shell->cmds[i]->skip_all_execution == false))
			{
				if (rlt_slm && shell->cmds[i]->fd_of_heredoc != -1)
				{
					close(shell->cmds[i]->fd_of_heredoc);
					shell->cmds[i]->fd_of_heredoc = -1;
				}
				process_heredoc(shell, shell->cmds[i], j);
				j++;
			}
		}
		if (shell->cmds[i]->skip_all_execution)
			return (close_wth_free(FT, shell->cmds, shell->cmds[i]->fd_of_heredoc));
	}
	return (3);
}