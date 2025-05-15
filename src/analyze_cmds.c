#include "../includes/mini.h"

int my_strcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)  // Check for NULL strings
    {
        printf("Error: NULL pointer passed to my_strcmp\n");
        return -1;  // Return a value to indicate the error
    }

    const unsigned char *s1_ptr = (const unsigned char *)s1;
    const unsigned char *s2_ptr = (const unsigned char *)s2;
    size_t i = 0;

    while (s1_ptr[i] == s2_ptr[i] && s1_ptr[i])
        i++;

    return (s1_ptr[i] - s2_ptr[i]);  // Return the difference if the strings are not equal
}

int is_operator(const char *arg)
{
	if (!arg)
		return (0);
	return (my_strcmp(arg, "<<") == 0
		|| my_strcmp(arg, "<") == 0
		|| my_strcmp(arg, ">>") == 0
		|| my_strcmp(arg, ">") == 0
		|| my_strcmp(arg, "|") == 0);
}


int count_max_commands(t_shell *shell)
{
    int count = 0;
    int i = 0;

    if (!shell || !shell->analyzing_data.args)
        return 0;

    while (shell->analyzing_data.args[i])
    {
        if (i == 0 && !is_operator(shell->analyzing_data.args[i]))
        {
            count++;
        }
        else if (i > 0 && is_operator(shell->analyzing_data.args[i - 1])
            && !is_operator(shell->analyzing_data.args[i])
            && my_strcmp(shell->analyzing_data.args[i - 1], "|") == 0)
        {
            count++;
        }
        i++;
    }
    shell->analyzing_data.cmds_count = count;
    return count;
}



// int	count_max_commands(t_shell *shell)
// {
// 	int	count;
// 	int	i;

// 	if (!shell->analyzing_data.args || !shell)
// 		return (0);
// 	count = 0;
// 	i = 0;

// 	// Print arguments for debugging (optional)
// 	// print_args(shell->analyzing_data.args);

// 	while (shell->analyzing_data.args[i])
// 	{
// 		if (my_strcmp(shell->analyzing_data.args[i], "<<") != 0
// 			&& my_strcmp(shell->analyzing_data.args[i], "<") != 0
// 			&& my_strcmp(shell->analyzing_data.args[i], ">>") != 0
// 			&& my_strcmp(shell->analyzing_data.args[i], ">") != 0
// 			&& my_strcmp(shell->analyzing_data.args[i], "|") != 0 && (i == 0
// 				|| (my_strcmp(shell->analyzing_data.args[i - 1], "<<") != 0
// 					&& my_strcmp(shell->analyzing_data.args[i - 1], "<") != 0
// 					&& my_strcmp(shell->analyzing_data.args[i - 1], ">>") != 0
// 					&& my_strcmp(shell->analyzing_data.args[i - 1], ">") != 0)))
// 		{
// 			count++;
// 			shell->analyzing_data.cmds_count++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

void	command_count(t_shell *shell)
{
	int x;

	if (!shell)
		return ;

	// Get the maximum number of commands
	x = count_max_commands(shell);
	printf("Total valid commands counted: %d\n", x);

	// Allocate memory for the commands array (3D pointer)		// Below Was  Working 100% but i will do structures instead of string
	// if (!(x > shell->analyzing_data.pipes_num))
	// 	shell->cmds = malloc(sizeof(char ***) * (shell->analyzing_data.pipes_num + 2));  // +2 for pipes
	// else if (x > shell->analyzing_data.pipes_num)
	// 	shell->cmds = malloc(sizeof(char ***) * (x + 1));  // +1 for null terminator

	// if (!shell->cmds)
	// {
	// 	printf("Memory allocation failed for command array\n");
	// 	return ;
	// }
}

void	analyze_cmds(t_shell *shell, int i, int j)
{
	if (!shell)
		return ;

	// Count the number of valid commands
	// print_args(shell->analyzing_data.args);	
	// printf("Total valid commands counted: %d\n", i);	// TEST (3) - Worked
	
	// Below was working 100% but i will do structures instead of string
	// if (!j && i <= shell->analyzing_data.pipes_num)
	// 	shell->cmds = malloc(sizeof(char ***) * (shell->analyzing_data.pipes_num + 2));
	// else
	// 	shell->cmds = malloc(sizeof(char ***) * (i + 1));
}
