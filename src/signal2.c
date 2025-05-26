#include "../includes/mini.h"

static void behaviour(int sig)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sig_intrctvly(int sig)
{
	if (sig == SIGINT)
	{
		behaviour(sig);
	}
}

void	set_all_signals(void)
{
	signal(SIGINT, handle_sig_intrctvly);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

static void handle_herdoc_intrctve(int sig)
{
	if (sig == SIGINT)
	{
		g_cnt_be_interrupted = 130;
		behaviour(sig);
	}
}

int apply_signals(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, handle_herdoc_intrctve);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
}

