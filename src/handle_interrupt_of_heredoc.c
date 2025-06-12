/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_interrupt_of_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:20:20 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:20:21 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/* For signals
int	handle_interrupt_of_heredoc(size_t rlk,  t_command_data *cmd, bool is_rlm)
{
	int	new_stdin_interrupt;
	int	flush_flag;

	if (rlk || is_rlm == true)
	{
		if (is_rlm == true)
			new_stdin_interrupt = open("/dev/tty", O_RDONLY);
		if (rlk && new_stdin_interrupt != -1)
		{
			dup2(new_stdin_interrupt, STDIN_FILENO);
			flush_flag = 0;
			ioctl(new_stdin_interrupt, TCFLSH, &flush_flag);
		}
		cmd->skip_all_execution = true;
	}
	return (1);
}
*/