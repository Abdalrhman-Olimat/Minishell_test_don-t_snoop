/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal_handler.c                           :+:      ::::::::   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 09:32:12 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}
