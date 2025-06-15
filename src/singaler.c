#define _POSIX_C_SOURCE 200809L
#include "../includes/mini.h"
#include <signal.h>

volatile sig_atomic_t g_signal = 0;

// Function to handle Ctrl+C in prompt mode
static void restore_prompt(int sig)
{
    g_signal = sig;
    write(STDOUT_FILENO, "\n", 1);  // Write newline after SIGINT
    rl_replace_line("", 1);        // Replace the line in the prompt
    rl_on_new_line();              // Move to new line
    rl_redisplay();                // Redisplay the prompt
}

// Setup signal handling for interactive prompt mode (Ctrl+C)
void setup_prompt_signal(void)
{
    struct sigaction sa;

    sa.sa_handler = restore_prompt;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);  // Set handler for SIGINT
    signal(SIGQUIT, SIG_IGN);      // Ignore SIGQUIT
    signal(SIGTSTP, SIG_IGN);      // Ignore SIGTSTP
}

/*
volatile sig_atomic_t	g_signal = 0;

static void	restore_prompt(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	signal_handler(int sig)
{
	g_signal = sig;
}

void	setup_prompt_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = restore_prompt;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	setup_default_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
*/