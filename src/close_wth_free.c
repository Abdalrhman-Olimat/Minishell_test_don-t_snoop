/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_wth_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:06:26 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 11:31:35 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	close_wth_free(size_t risgo_vsnot, t_command_data **cmds, int fd)
{
	if (risgo_vsnot)
	{
		close(fd);
		free_big_malloc_cmds(0, cmds, -1);
		return (0);
	}
	return (1);
}
