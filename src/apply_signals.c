#include "../includes/mini.h"

void	apply_sig_action(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_interrupted = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int apply_signals(int s_flg)
{

	if (s_flg < 0)
		return (0);
	else 
	{
		signal(SIGINT, apply_sig_action);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	return (1);
}