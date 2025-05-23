#include "../includes/mini.h"

static int open_and_proceed(t_shell *shell, t_input *token, int *cmd_i, t_command_data **cmd)
{
	int fd;
	
	fd = open(token->next->string, O_RDONLY);
	if (fd != -1)
	{
		cmd[*cmd_i]->content_analyze.is_there_infile = true;
		close(fd);
		token = token->next;
		ft_strlcpy(cmd[*cmd_i]->in_file, token->string, MAXIMUM_FILENAME_SIZE);
		return (3);
	}
	return (fd);
}

int handle_redir_in(t_shell *shell, t_input *token, int *cmd_i, t_command_data **cmd)
{
	int fd;

	fd = open_and_proceed(shell, token, cmd_i, cmd);
	if (fd == -1)
	{
		alert_err_of_file(token->next->string);
		set_status_skip(shell, cmd, cmd_i, 1);
		return (0);
	}
}
