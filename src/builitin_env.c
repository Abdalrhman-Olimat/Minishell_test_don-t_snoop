#include "../includes/mini.h"

int ft_env(char **argv, char **envp)
{
    int i;

    // Check if there are any arguments besides the command name "env"
    if (argv[1] != NULL)
    {
        write(2,"env: too many arguments\n", 25);
        return (1);
    }

    // Loop through the environment variables and print each one
    i = 0;
    while (envp[i] != NULL)
    {
        printf("%s\n", envp[i]);
        i++;
    }

    // Return success
    return (0);
}
