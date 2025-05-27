#include "../includes/mini.h"

void	process_cmd_quoted_error(t_shell *shell, t_command_data *cmds)
{
	char	**test_split;

	if (!cmds || !cmds->cmd_splitted || !cmds->cmd_splitted[0])
		return ;
	if (cmds->cmd_splitted[0] != NULL)
	{
		test_split = ft_split(cmds->cmd_splitted[0], ' ');
		if (!test_split)
			return ;
		if (test_split[0] && test_split[1])
		{
			ft_putstr_fd(cmds->cmd_splitted[0], STDERR_FILENO);
			ft_putstr_fd(" : command not found\n", STDERR_FILENO);
			shell->exit_status = 127;
			cmds->skip_cmd = 1;
		}
		free_2d_arr(test_split);
	}
}
