/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singaler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:21:04 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:21:22 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#include "../includes/mini.h"
#include <signal.h>

volatile sig_atomic_t g_signal = 0;

static void restore_prompt(int sig)
{
    g_signal = sig;
    write(STDOUT_FILENO, "\n", 1);  
    rl_replace_line("", 1);        
    rl_on_new_line();              
    rl_redisplay();               
}

void setup_prompt_signal(void)
{
    struct sigaction sa;

    sa.sa_handler = restore_prompt;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);  
    signal(SIGQUIT, SIG_IGN);      
    signal(SIGTSTP, SIG_IGN);      
}
