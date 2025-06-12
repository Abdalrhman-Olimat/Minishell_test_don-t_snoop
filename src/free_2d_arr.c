/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:53:56 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:07:43 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	free_2d_arr(char **string)
{
	int	i;

	if (!string)
		return ;
	i = 0;
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
}
