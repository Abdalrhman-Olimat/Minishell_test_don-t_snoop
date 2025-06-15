/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmad <ahmad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 06:02:38 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 09:26:35 by ahmad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void reset_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
}
// static void	behaviour(int sig)
// {
// 	ft_putstr_fd("\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	g_signal = 130;
// }

// void	handle_sig_intrctvly(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		behaviour(sig);
// 	}
// }

// void	set_all_signals(void)
// {
// 	signal(SIGINT, handle_sig_intrctvly);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGTSTP, SIG_IGN);
// }

// static void	handle_herdoc_intrctve(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_signal = 130;
// 		behaviour(sig);
// 	}
// }

// int	apply_signals(int mode)
// {
// 	if (mode == 1)
// 	{
// 		signal(SIGINT, handle_herdoc_intrctve);
// 		signal(SIGQUIT, SIG_IGN);
// 		signal(SIGTSTP, SIG_IGN);
// 	}
// 	return (1);
// }
