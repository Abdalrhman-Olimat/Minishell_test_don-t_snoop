#include "../includes/mini.h"

int set_working_cmd(t_shell *shell, t_command_data *command)
{
	int			i;
	struct stat	path_stat;

	if (access (command->cmd_splitted[0], X_OK) == 0)
	{
		if (stat(command->cmd_splitted[0], &path_stat) == 0
			&& S_ISDIR(path_stat.st_mode))
		{
			// print_dir_error(command);
			char	*err_msg;

			err_msg = ft_strjoin(command->cmd_splitted[0], " : Is a directory\n");
			write(2, err_msg, ft_strlen(err_msg));
			free(err_msg);
			free_both_envp_paths(shell);
			free_big_malloc_cmds(126, command->main_cmd, -1);
			exit(126);
		}
		command->cmd_path = ft_strdup(command->cmd_splitted[0]);
		return (0);
	}
	i = -1;
	while (shell->analyzing_data.path[++i])
	{
		char		*tmp;

		tmp = ft_strjoin(shell->analyzing_data.path[i], "/");
		command->cmd_path = ft_strjoin(tmp, command->cmd_splitted[0]);
		free(tmp);
		if (access(command->cmd_path , X_OK) == 0)
			break ;
		free(command->cmd_path);
	}
	if (shell->analyzing_data.path[i] == NULL)
	{
		// print_not_found(cmd, path);
		char	*err_nt_found_msg;

		err_nt_found_msg = ft_strjoin(command->cmd_splitted[0], " : command isn't found\n");
		write(2, err_nt_found_msg, ft_strlen(err_nt_found_msg));
		free(err_nt_found_msg);
		free_cmds_all(command->main_cmd, 127, -1);
		free_both_envp_paths(shell);
		exit(127);
	}
	return (0);
}