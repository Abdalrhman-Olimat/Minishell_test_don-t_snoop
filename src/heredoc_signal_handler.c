#include "../includes/mini.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_heredoc_interrupted = 1;
		close(0);
	}
}