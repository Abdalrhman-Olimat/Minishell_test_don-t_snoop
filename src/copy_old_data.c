/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_old_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:07:38 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:02:48 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static char	**allocate_2d_block(int size)
{
	char	**block;

	block = malloc(sizeof(char *) * size);
	return (block);
}

static int	duplicate_each_entry(char **dst, char **src, int count)
{
	int		idx;
	size_t	len;

	idx = 0;
	while (idx < count)
	{
		len = ft_strlen(src[idx]) + 1;
		dst[idx] = malloc(len);
		if (!dst[idx])
			return (0);
		ft_strlcpy(dst[idx], src[idx], len);
		idx++;
	}
	return (1);
}

static void	cleanup_allocs(char **arr, int last)
{
	while (--last >= 0)
		free(arr[last]);
	free(arr);
}

char	**copy_old_data(int old_len, int new_len, char **old_str)
{
	char	**new_data;

	if (!old_str)
		return (NULL);
	new_data = allocate_2d_block(new_len);
	if (!new_data)
	{
		free_2d_arr(old_str);
		return (NULL);
	}
	if (!duplicate_each_entry(new_data, old_str, old_len))
	{
		cleanup_allocs(new_data, old_len);
		free_2d_arr(old_str);
		return (NULL);
	}
	free_2d_arr(old_str);
	return (new_data);
}
