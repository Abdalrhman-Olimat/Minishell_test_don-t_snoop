/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_ft_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:03:15 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/29 04:02:59 by aeleimat         ###   ########.fr       */
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
	
	// Allocate new memory block
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	
	// Initialize memory to zero (ensures all bytes are initialized)
	ft_memset(newptr, 0, newsize);
	
	// Calculate how much data to copy from the old pointer
	src_ptr = (char *)ptr;
	oldsize = 0;
	while (src_ptr[oldsize] != '\0' && oldsize < newsize - 1)
		oldsize++;
	
	// Copy data from old pointer to new pointer
	if (oldsize > 0)
		ft_memcpy(newptr, ptr, oldsize);
	
	// Free the old pointer
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
