/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:55:21 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:00:54 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	track_heredoc_node(t_heredoc_tracker *tracker, t_input *node)
{
	if (!tracker || !node)
		return ;
	if (tracker->count < 99)
		tracker->nodes[tracker->count++] = node;
}

void	free_tracked_heredoc_nodes(t_heredoc_tracker *tracker)
{
	int	i;

	if (!tracker || tracker->count <= 0)
		return ;
	i = 0;
	while (i < tracker->count && i < 100)
	{
		if (tracker->nodes[i])
		{
			if (tracker->nodes[i]->string
				&& tracker->nodes[i]->string != (char *)0x1
				&& tracker->nodes[i]->string != (char *)0x2
				&& tracker->nodes[i]->string != (char *)0x3)
			{
				free(tracker->nodes[i]->string);
			}
			free(tracker->nodes[i]);
			tracker->nodes[i] = NULL;
		}
		i++;
	}
	tracker->count = 0;
}
