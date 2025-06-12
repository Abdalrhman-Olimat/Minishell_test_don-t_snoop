/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:13:25 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:13:26 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static bool	try_open_infile(const char *filename)
{
	int	fd;

	if (access(filename, R_OK) == 0)
		return (true);
	else
		return (false);
}

static void	register_valid_infile(t_input **token, t_command_data *cmd)
{
	(*token) = (*token)->next;
	cmd->content_analyze.is_there_infile = true;
	ft_strlcpy(cmd->in_file, (*token)->string, MAXIMUM_FILENAME_SIZE);
}

int	handle_redir_in(t_shell *shell, t_input **token, int *cmd_i,
		t_command_data **cmds)
{
	char	*filename;
	int		fd;

	if (!token || !*token || !(*token)->next)
		return (0);
	filename = (*token)->next->string;
	fd = try_open_infile(filename);
	if (fd == false)
	{
		alert_err_of_file(filename);
		set_status_skip(shell, cmds, cmd_i, 1);
		(*token) = (*token)->next;
		return (0);
	}
	register_valid_infile(token, cmds[*cmd_i]);
	return (3);
}

/*
static int	open_and_proceed(t_shell *shell, t_input **token, int *cmd_i,
		t_command_data **cmd)
{
	int	fd;

	
	fd = open((*token)->next->string, O_RDONLY);
	if (fd != -1)
	{
		cmd[*cmd_i]->content_analyze.is_there_infile = true;
		close(fd);
		(*token)= (*token)->next;
		ft_strlcpy(cmd[*cmd_i]->in_file, (*token)->string,
				MAXIMUM_FILENAME_SIZE);
		return (3);
	}
	return (fd);
}

int	handle_redir_in(t_shell *shell, t_input **token, int *cmd_i,
		t_command_data **cmd)
{
	int	fd;

	fd = open_and_proceed(shell, token, cmd_i, cmd);
	if (fd == -1)
	{
		alert_err_of_file((*token)->next->string);
		set_status_skip(shell, cmd, cmd_i, 1);
		return (0);
	}
}
*/