/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:11:55 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:20:07 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	put_and_free(char **str, int fd_outstream)
{
	if (str && *str)
	{
		ft_putendl_fd(*str, fd_outstream);
		free(*str);
		*str = NULL;
		*str = readline("> ");
	}
}

void	handle_heredoc_input(int fd_outstream, t_command_data *cmd,
		int delem_index)
{
	char	*entered_line;
	int		fd;
	int		behavior;

	fd = -1;
	behavior = 0;
	if (FT)
	{
		init_herdoc_signals(3);
		entered_line = readline("> ");
		while (FT && entered_line != NULL
			&& ft_strncmp(entered_line, cmd->delim[delem_index],
				MAXIMUM_CMD_SIZE) != 0)
			put_and_free(&entered_line, fd_outstream);
		if (FT > 0 && entered_line == NULL && g_cnt_be_interrupted)
			fix_heredoc_interruption(FT, cmd, &fd, &behavior);
		free(entered_line);
	}
}
