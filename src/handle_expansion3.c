/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:11:50 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:11:51 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	is_valid_str_dup(char **dst, char *src)
{
	*dst = ft_strdup(src);
	return (*dst != NULL);
}

static void	advance_indexes(int *dst_i, int *src_i)
{
	(*dst_i)++;
	(*src_i)++;
}

int	copy_one_by_one(char **dst, char **src, int *dst_i, int *src_i)
{
	while (src[*src_i])
	{
		if (!is_valid_str_dup(&dst[*dst_i], src[*src_i]))
			return (0);
		advance_indexes(dst_i, src_i);
	}
	dst[*dst_i] = NULL;
	return (1);
}
