#include "../includes/mini.h"

static int	safe_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	return (0);
}

static void  set_both(int *older_pipe, int *pipe_fd, bool use_both)
{
	older_pipe[0] = pipe_fd[0];
	older_pipe[1] = pipe_fd[1];
}

static int set_in_only(int *older_pipe, int *pipe_fd, bool use_both)
{
	older_pipe[0] = pipe_fd[0];
	older_pipe[1] = -1;
	return (0);
}

static void	set_pipe_state(int *older_pipe, int *pipe_fd, bool use_both)
{
	if (use_both)
	{
		set_both(older_pipe, pipe_fd, true);
	}

	else
	{
		set_in_only(older_pipe, pipe_fd, false);
	}
}

int switch_pipes(int *pipe_fd, int *older_pipe, t_command_data **cmd, int i)
{
	bool does_needing_pipe;
	bool has_next_in;

	if (i > 0)
		if (cmd[i - 1]->content_analyze.is_there_pipe)
		{
			safe_close(&older_pipe[0]);
			safe_close(&older_pipe[1]);
		}
	does_needing_pipe = cmd[i]->content_analyze.is_there_pipe;
	has_next_in = cmd[i + 1] && (cmd[i + 1]->content_analyze.is_there_infile 
		|| cmd[i + 1]->content_analyze.is_there_heredoc);
	if (does_needing_pipe)
		set_pipe_state(older_pipe, pipe_fd, !has_next_in);
	else
		set_pipe_state(older_pipe, (int [2]){-1, -1}, true);
	return (0);
}

/*
int switch_pipes(int *pipe_fd, int *prev_pipe, t_command_data **cmd, int i)
{
	if (i > 0 && cmd[i - 1]->content_analyze.is_there_pipe)
	{
		close(prev_pipe[0]);
		if (prev_pipe[1] != -1)
			close(prev_pipe[1]);
	}
	if (cmd[i]->content_analyze.is_there_pipe)
	{
		if (cmd[i + 1] && (cmd[i + 1]->content_analyze.is_there_infile 
			|| cmd[i + 1]->content_analyze.is_there_heredoc))
		{
			close(pipe_fd[1]);
			prev_pipe[0] = pipe_fd[0];
			prev_pipe[1] = -1;
		}
		else
		{
			prev_pipe[0] = pipe_fd[0];
			prev_pipe[1] = pipe_fd[1];
		}
	}
	else
	{
		prev_pipe[0] = -1;
		prev_pipe[1] = -1;
	}
	return (0);
}
*/