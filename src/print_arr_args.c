/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arr_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:45:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:45:53 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	print_args(char **args)
{
	int	i;

	if (!args)
	{
		printf("Args: (null)\n");
		return ;
	}
	i = 0;
	while (args[i])
	{
		printf("Arg[%d]: \"%s\"\n", i, args[i]);
		i++;
	}
}
