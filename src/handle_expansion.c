#include "../includes/mini.h"

char	**realloc_2d_appending(char **old, int old_size, int new_size)
{
	char	**new_arr;
	int		i;

	new_arr = (char **)malloc(sizeof(char *) * (new_size + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_arr[i] = old[i];
		i++;
	}
	while (i < new_size)
	{
		new_arr[i] = NULL;
		i++;
	}
	new_arr[new_size] = NULL;
	free(old);
	return (new_arr);
}



int append_args_safely(char ***args_ref, char **suffix, int skip)
{
	int start_index;

	start_index = get_2d_len(*args_ref);
	*args_ref = allocate_expanded_args(*args_ref, suffix, skip);
	if (!*args_ref)
		return (0);
	return (copy_suffix(*args_ref, suffix,
			 start_index, skip));
}

int handle_expansion(t_shell *shell, t_command_data *cmd)
{
	char **tokens;

	if (!was_expansion_needed(cmd))
		return (0);
	tokens = split_primary_argument(cmd);
	if (tokens == NULL)
		return (1);
	if (!add_remaining_arguments(&tokens, cmd->cmd_splitted))
	{
		free_2d_arr(tokens);
		return (2);
	}
	update_command_and_path(shell, cmd, tokens);
	return (0);
}

/*
int	append_args_safely(char ***args_ref, char **suffix, int skip)
{
	int	original;
	int	additional;
	int	i;
	int	j;

	original = get_2d_len(*args_ref);
	additional = get_2d_len(suffix) - skip;
	*args_ref = realloc_2d_appending(*args_ref, original, original + additional);
	if (!*args_ref)
		return (0);
	i = original;
	j = skip;
	while (suffix[j])
	{
		(*args_ref)[i] = ft_strdup(suffix[j]);
		if (!(*args_ref)[i])
			return (0);
		i++;
		j++;
	}
	(*args_ref)[i] = NULL;
	return (1);
}
*/
/*
int	handle_expansion(t_shell *shell, t_command_data *cmd)
{
	char	**new_args;

	if (cmd->was_quoted == 1)
		return (1);
	if (!ft_strchr(cmd->cmd_splitted[0], ' '))
		return (2);
	new_args = ft_split(cmd->cmd_splitted[0], ' ');
	if (!new_args)
		return (3);
	if (cmd->cmd_splitted[1])
	{
		if (!append_args_safely(&new_args, cmd->cmd_splitted, 1))
			return (4);
	}
	free_2d_arr(cmd->cmd_splitted);
	cmd->cmd_splitted = new_args;
	set_working_cmd(shell, cmd);
	return (0);
}
*/
/*
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
		// end

	}
	if (!new_args)
		return (4);
	free_2d_arr(command->cmd_splitted);
	command->cmd_splitted = new_args;
	set_working_cmd(shell, command);
	return (0);
}
*/
