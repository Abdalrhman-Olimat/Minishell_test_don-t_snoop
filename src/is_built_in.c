#include "../includes/mini.h"

int	is_built_in(t_command_data *command)
{
	if (!command->cmd_splitted || command->cmd_splitted[0] == NULL)
		return (0);
	if (!ft_strcmp(command->cmd_splitted[0], "cd"))
		return (1);
	if (!ft_strcmp(command->cmd_splitted[0], "echo"))
		return (1);
	if (!ft_strcmp(command->cmd_splitted[0], "pwd"))
		return (1);
	if (!ft_strcmp(command->cmd_splitted[0], "export"))
		return (1);
	if (!ft_strcmp(command->cmd_splitted[0], "unset"))
		return (1);
	if (!ft_strcmp(command->cmd_splitted[0], "env"))
		return (1);
	if (!ft_strcmp(command->cmd_splitted[0], "exit"))
		return (1);
	return (0);
}