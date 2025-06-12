/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:26:45 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 05:26:46 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

bool	matches_redirection(const char *token)
{
	return (my_strcmp(token, "<") == 0 || my_strcmp(token, ">") == 0);
}

bool	matches_double_redirection(const char *token)
{
	return (my_strcmp(token, "<<") == 0 || my_strcmp(token, ">>") == 0);
}

bool	is_pipe_token(const char *token)
{
	return (my_strcmp(token, "|") == 0);
}
