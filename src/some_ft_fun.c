/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_ft_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:03:15 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 06:03:00 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	oldsize;
	char	*src_ptr;

	if (ptr == 0)
		return (malloc(newsize));
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	ft_memset(newptr, 0, newsize);
	src_ptr = (char *)ptr;
	oldsize = 0;
	while (src_ptr[oldsize] != '\0' && oldsize < newsize - 1)
		oldsize++;
	if (oldsize > 0)
		ft_memcpy(newptr, ptr, oldsize);
	free(ptr);
	return (newptr);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		dst[i] = '\0';
	}
	return (dst);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
