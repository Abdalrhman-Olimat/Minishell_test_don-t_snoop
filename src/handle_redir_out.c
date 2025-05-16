#include "../includes/mini.h"

int handle_redir_out(t_shell *shell, t_input *token, t_command_data **cmd, int *cmd_i)
{
	int	fd;

	fd = open(token->next->string , O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		alert_err_of_file(token->next->string);
		set_status_skip(shell, cmd, cmd_i, 1);
		return (0);
	}
	
	cmd[*cmd_i]->content_analyze.is_there_outfile = true;
	close(fd);
	token = token->next;
	ft_strlcpy(cmd[*cmd_i]->out_file, token->string, MAXIMUM_FILENAME_SIZE);
	return (3);
}