#include "../includes/mini.h"

int handle_no_pipes_command(t_command_data *command, int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = -1;
	*stdout_backup = -1;

	if ((command->content_analyze.is_there_appendfile ||
		 command->content_analyze.is_there_infile ||
		 command->content_analyze.is_there_outfile)
		&& is_built_in(command))
		change_redirections(command, stdin_backup, stdout_backup);
	// if (command->command_split && command->command_split[0]				// TODO- Maybe need to do this function
	// 	&& ft_strchr(command->command_split[0], ' ') && command->was_quoted != 1)
	// 	handle_unquoted_spaces(command);
}
