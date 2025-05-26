#include "../includes/mini.h"

volatile sig_atomic_t	g_cnt_be_interrupted = 0;



static void fix_operations(int *behaviour_code, int fixed_new_stdin, t_command_data *cmd)
{
	cmd->skip_all_execution = 1;
	dup2(fixed_new_stdin, STDIN_FILENO);
	*behaviour_code = 0;
	ioctl(fixed_new_stdin, TCFLSH, behaviour_code);
}

void fix_heredoc_interruption(t_shell_returns code, t_command_data *cmd, int *fixed_new_stdin, int *behaviour_code)
{
	if (code == FT)
		*fixed_new_stdin = open("/dev/tty", O_RDONLY);
	if (*fixed_new_stdin == -1)
	{
		ft_putstr_fd("Error: Unable to open /dev/tty (for heredoc error fixing)\n", 2);
		return;
	}
	else
		fix_operations(behaviour_code, *fixed_new_stdin, cmd);
}


static void apply_init_herdoc_signls(int sig)
{
	if (sig == SIGINT)
	{
		g_cnt_be_interrupted = 1;
		ft_putstr_fd("\n", 1);
		close(STDIN_FILENO);
	}
}

int init_herdoc_signals(int s_flg)
{
	g_cnt_be_interrupted = 0;
	signal(SIGINT, apply_init_herdoc_signls);
	return (0);
}
/*
void	apply_sig_action(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
*/