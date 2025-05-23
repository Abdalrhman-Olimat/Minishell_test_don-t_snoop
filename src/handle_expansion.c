#include "../includes/mini.h"

int handle_expansion(t_shell *shell, t_command_data *command)
{
	char	**new_args;
	int i;
	int j;

	if (command->was_quoted == 1)
		return (1);
	if (!ft_strchr(command->cmd_splitted[0], ' '))
		return (2);
	new_args = ft_split(command->cmd_splitted[0], ' ');
	if (!new_args)
		return (3);
	if (command->cmd_splitted[1])
	{
		// append_args(&new_args, command); start
		i = 0;
		while ((*new_args)[i])
			i++;
		j = 1;
		while (command->cmd_splitted[j])
			j++;
		new_args = copy_old_data(i, i + j, new_args);
		if (!*new_args)
			return 1;
		j = 1;
		while (command->cmd_splitted[j])
		{
			new_args[i] = ft_strdup(command->cmd_splitted[j]);
			if (!new_args[i])
				return 1;
			i++;
			j++;
		}
		new_args[i] = NULL;
		/*end*/

	}
	if (!new_args)
		return (4);
	free_2d_arr(command->cmd_splitted);
	command->cmd_splitted = new_args;
	set_working_cmd(shell, command);
	return (0);
}
