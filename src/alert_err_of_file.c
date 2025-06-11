/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alert_err_of_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:53:07 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/11 14:53:09 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	alert_err_of_file(char *filename)
{
	char	*temp1;

	if (!temp1)
		return ;
	temp1 = ft_strjoin("Shell error: ", ft_strjoin(filename,
				": No such file or directory\n"));
	if (!temp1)
		return ;
	write(2, temp1, ft_strlen(temp1));
	free(temp1);
}
