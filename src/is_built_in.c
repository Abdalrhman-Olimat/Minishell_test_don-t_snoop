#include "../includes/mini.h"

static int check_match(char *input, const char *builtin)
{
	return ft_strncmp(input, builtin, 8) == 0;
}

int	is_built_in(t_command_data *command)
{
	char *name;
	int i;
	static const char *built_in_commands[] = {
		"cd",
		"echo",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};


	if (!command || !command->cmd_splitted || !command->cmd_splitted[0])
		return (0);

	name = command->cmd_splitted[0];
	i = -1;

	while (built_in_commands[++i])
	{
		if (check_match(name, built_in_commands[i]))
			return (1);
	}
	
	return (0);
}