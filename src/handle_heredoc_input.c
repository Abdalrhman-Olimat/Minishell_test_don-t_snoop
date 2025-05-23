#include "../includes/mini.h"

static void put_and_free(char **str, int fd_outstream)
{
	if (str && *str)
	{
		ft_putendl_fd(*str, fd_outstream);
		free(*str);
		*str = NULL;
		*str = readline("> ");
	}
}

void handle_heredoc_input(int fd_outstream,  t_command_data *cmd, int delem_index)
{
	char	*entered_line;

	// g_heredoc_interrupted = 0;
	if (FT)
	{
		// signal(SIGINT, heredoc_signal_handler);
		entered_line = readline("> ");
		while (FT && entered_line != NULL &&
				 ft_strncmp(entered_line, cmd->delim[delem_index], MAXIMUM_CMD_SIZE) != 0)
		{
			put_and_free(&entered_line, fd_outstream);
		}
		// if (FT > 0 && !entered_line && g_heredoc_interrupted)
			// handle_interrupt_of_heredoc(FT, cmd, true);
		free(entered_line);
	}
}