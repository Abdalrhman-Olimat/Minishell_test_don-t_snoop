#include "../includes/mini.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int ft_echo(char **argv)
{
    int i = 1;                // Start after "echo" (argv[0])
    int suppress_newline = 0; // Flag to suppress trailing newline

    // Handle case with no arguments
    if (argv[1] == NULL)
    {
        printf("\n");
        return 0;
    }

    // Consume all leading "-n" options
    while (argv[i] != NULL && ft_strcmp(argv[i], "-n") == 0)
    {
        suppress_newline = 1;
        i++;
    }

    // Print remaining arguments with spaces between them
    int first = 1; // Flag to avoid leading space
    while (argv[i] != NULL)
    {
        if (!first)
            printf(" ");     // Print space before all but the first argument
        printf("%s", argv[i]); // Print the argument
        first = 0;           // Clear flag after first argument
        i++;
    }

    // Print newline unless suppressed
    if (!suppress_newline)
        printf("\n");

    return 0;
}

/*
int main(int argc, char **argv)
{
    if (ft_strcmp(argv[1], "echo") == 0)
	return(ft_echo(argv));
}
*/