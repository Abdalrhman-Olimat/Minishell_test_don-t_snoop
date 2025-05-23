/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_ft_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:03:15 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/22 01:40:08 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	copy_size;
	char	*src_ptr;
	char	*dst_ptr;
	size_t	i;

	if (ptr == 0)
		return (malloc(newsize));
	newptr = malloc(newsize);
	if (!newptr)
		return (NULL);
	src_ptr = (char *)ptr;
	dst_ptr = newptr;
	i = 0;
	copy_size = newsize;
	while (i < copy_size && src_ptr[i] != '\0')
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	if (i < newsize)
		dst_ptr[i] = '\0';
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
