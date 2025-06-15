/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_working_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:02:17 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:20:14 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	handle_directory(t_shell *sh, t_command_data *cmd)
{
	struct stat	info;
	char		*msg;
	int			token_count;

	token_count = 0;
	if (stat(cmd->cmd_splitted[0], &info) == 0 && S_ISDIR(info.st_mode))
	{
		msg = ft_strjoin(cmd->cmd_splitted[0], " : Is a directory\n");
		write(2, msg, ft_strlen(msg));
		free(msg);
		if (sh->tokens)
			token_count = count_tokens(sh->tokens);
		if (sh->tokens_header)
			free_list(sh->tokens_header);
		if (sh->analyzing_data.args)
			free_token_array(sh->analyzing_data.args, token_count);
		if (sh->tokens)
			free_list(sh->tokens);
		free_both_envp_paths(sh);
		if (sh && sh->cmds)
			free_big_malloc_cmds(126, sh->cmds, -1);
		sh->exit_status = 126;
		exit(126);
	}
}

static int	try_direct_path(t_shell *sh, t_command_data *cmd)
{
	if (cmd->cmd_splitted[0][0] == '/' || ft_strchr(cmd->cmd_splitted[0], '/'))
	{
		if (access(cmd->cmd_splitted[0], X_OK) != 0)
		{
			char *msg = ft_strjoin(cmd->cmd_splitted[0], ": No such file or directory\n");
			write(2, msg, ft_strlen(msg));
			free(msg);
			free_cmds_all(sh->cmds, sh->analyzing_data.cmds_count, 0);
			free_both_envp_paths(sh);
			exit(127);
		}
		handle_directory(sh, cmd);
		cmd->cmd_path = ft_strdup(cmd->cmd_splitted[0]);
		return (1);
	}
	if (access(cmd->cmd_splitted[0], X_OK) != 0)
		return (0);
	handle_directory(sh, cmd);
	cmd->cmd_path = ft_strdup(cmd->cmd_splitted[0]);
	return (1);
}

static void	not_found_exit(t_shell *sh, t_command_data *cmd)
{
	char	*msg;
	int		token_count;

	token_count = 0;
	sh->exit_status = 127;
	msg = ft_strjoin(cmd->cmd_splitted[0], ": command not found\n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	if (sh->tokens)
		token_count = count_tokens(sh->tokens);
	if (sh->tokens_header)
		free_list(sh->tokens_header);
	if (sh->analyzing_data.args)
		free_token_array(sh->analyzing_data.args, token_count);
	if (sh->tokens)
		free_list(sh->tokens);
	if (sh && sh->cmds)
		free_big_malloc_cmds(0, sh->cmds, -1);
	free_both_envp_paths(sh);
	exit(127);
}

static int	search_path_list(t_shell *sh, t_command_data *cmd)
{
	int		i;
	char	*prefix;
	char	*full;

	i = -1;
	if (!sh->analyzing_data.path)
		return (0);
	while (sh->analyzing_data.path && sh->analyzing_data.path[++i])
	{
		prefix = ft_strjoin(sh->analyzing_data.path[i], "/");
		if (!prefix)
			continue ;
		full = ft_strjoin(prefix, cmd->cmd_splitted[0]);
		free(prefix);
		if (full && access(full, X_OK) == 0)
		{
			cmd->cmd_path = full;
			return (1);
		}
		if (full)
			free(full);
	}
	return (0);
}

int	set_working_cmd(t_shell *sh, t_command_data *cmd)
{
	refresh_path_cache(sh);
	if (try_direct_path(sh, cmd))
		return (0);
	if (search_path_list(sh, cmd))
		return (0);
	not_found_exit(sh, cmd);
	return (0);
}
