#include "../includes/mini.h"

int	ft_exit(char **args, t_shell *shell)
{
	int exit_code;

	ft_putendl_fd("exit", 1);

	// Check for too many arguments
	if (args[1] && args[2])
	{
		// Only show error for too many args if first arg is a valid number
		if (ft_isnumber(args[1]))
		{
			ft_putendl_fd("exit: too many arguments", 2);
			shell->exit_status = 1;
			return (1);  // Don't exit, just return with error
		}
	}

	// Process exit with a status code
	if (args[1])
	{
		if (ft_isnumber(args[1]))
		{
			exit_code = ft_atoi(args[1]) % 256;
			// Update shell exit status
			shell->exit_status = exit_code;
			
			// Call exit handler to clean up and exit
			ft_exit_handler(shell, NULL, NULL, exit_code);
		}
		else
		{
			// For non-numeric argument, exit with status 2
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit_code = 2;
			shell->exit_status = exit_code;
			
			// Call exit handler to clean up and exit
			ft_exit_handler(shell, NULL, NULL, exit_code);
		}
	}

	// No argument, use the current exit status
	exit_code = shell->exit_status;
	ft_exit_handler(shell, NULL, NULL, exit_code);
	
	return (0); // This is never reached, but prevents compiler warning
}

