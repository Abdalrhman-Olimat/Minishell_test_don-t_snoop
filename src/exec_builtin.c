/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmad <ahmad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:08:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 11:22:49 by ahmad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	exec_builtin(t_shell *shell, t_command_data *command, int *stdin_backup,
		int *stdout_backup)
{
	char	*cmd;

	cmd = command->cmd_splitted[0];
	if (!command->cmd_splitted || command->cmd_splitted[0] == NULL)
		return (0);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (ft_cd(command->cmd_splitted));
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ft_echo(command->cmd_splitted));
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (ft_exit(command->cmd_splitted, shell));
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (ft_export(command->cmd_splitted, &shell->analyzing_data,
				&command->is_from_expansion));
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (ft_unset(command->cmd_splitted, &shell->analyzing_data));
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (ft_env(command->cmd_splitted, shell->analyzing_data.envp));
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (ft_pwd());
	g_signal = 0;
	return (-1);
}
