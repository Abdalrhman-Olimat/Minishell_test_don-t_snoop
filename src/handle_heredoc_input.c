#include "../includes/mini.h"

void handle_heredoc_input(int fd_outstream,  t_command_data *cmd, int delem_index)
{
	char	*entered_line;

	g_heredoc_interrupted = 0;
	if (FT)
		signal(SIGINT, heredoc_signal_handler);
	entered_line = readline("> ");
	while (FT && entered_line != NULL &&
			 ft_strncmp(entered_line, cmd->delim[delem_index], MAXIMUM_CMD_SIZE) != 0)
	{
		ft_putendl_fd(entered_line, fd_outstream);
		free(entered_line);
		entered_line = readline("> ");
	}
	if (FT > 0 && !entered_line && g_heredoc_interrupted)
		handle_interrupt_of_heredoc(FT, cmd, true);
	free(entered_line);
}