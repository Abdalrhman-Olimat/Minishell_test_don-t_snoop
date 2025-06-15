/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:18:53 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:19:13 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	count = count_envp_length(envp);    
	if (count == 0)
		return ;
	sorted = copy_envp(envp, count);
	if (!sorted)
		return;
	sort_env(sorted, count);
	print_env(sorted);
}
