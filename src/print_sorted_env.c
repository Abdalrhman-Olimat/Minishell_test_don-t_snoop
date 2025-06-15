#include "../includes/mini.h"

/*
 * Counts the number of elements in the environment array
 */
int	count_envp_length(char **envp)
{
	int	count = 0;
	
	while (envp[count])
		count++;
	return (count);
}

/*
 * Copies the environment variables into a new array
 */
char	**copy_envp(char **envp, int count)
{
	int		i;
	char	**sorted;

	sorted = ft_calloc(count + 1, sizeof(char *));
	if (!sorted)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		sorted[i] = ft_strdup(envp[i]);
		i++;
	}
	sorted[i] = NULL;
	return (sorted);
}

/*
 * Sorts and prints the environment variables
 */
void	print_sorted_env(char **envp)
{
	int		count;
	char	**sorted;

	count = count_envp_length(envp);    // Count the number of environment variables
	if (count == 0)
		return ;
	sorted = copy_envp(envp, count);    // Copy environment variables
	if (!sorted)
		return;
	sort_env(sorted, count);            // Sort the environment variables
	print_env(sorted);                  // Print the sorted environment variables
}
