#include "../includes/mini.h"

/*
 * Handle the exit from the shell
 * 
 * shell: The shell structure to clean up
 * message: Custom message to display (optional)
 * error_msgs: Array of error messages to display (optional)
 * exit_code: The exit status to use
 */
void ft_exit_handler(t_shell *shell, char *message, char **error_msgs, int exit_code)
{
    int i;

    /* Set exit status in the shell structure */
    if (shell)
        shell->exit_status = exit_code;

    /* Display message if provided */
    if (message)
        ft_putendl_fd(message, 1);

    /* Display error messages if provided */
    if (error_msgs)
    {
        i = 0;
        while (error_msgs[i])
        {
            ft_putstr_fd(error_msgs[i], 2);
            i++;
        }
    }

    /* Clean up the shell before exit */
    cleanup_shell(shell);

    /* Free readline memory */
    rl_clear_history();

    exit(exit_code);
}
