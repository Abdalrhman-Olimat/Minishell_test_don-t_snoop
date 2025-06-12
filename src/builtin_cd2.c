/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:24:59 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 03:25:38 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*determine_target_dir(char **argv, char *old_pwd, int *print_flag)
{
	char	*target_dir;

	if (argv[1] == NULL)
	{
		target_dir = get_env("HOME");
		if (!target_dir)
		{
			fprintf(stderr, "cd: HOME not set\n");
			free(old_pwd);
			return (NULL);
		}
	}
	else if (argv[2] != NULL)
	{
		fprintf(stderr, "cd: too many arguments\n");
		free(old_pwd);
		return (NULL);
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		return (handle_cd_dash(old_pwd, print_flag));
	}
	else
		target_dir = argv[1];
	return (target_dir);
}

void	update_pwd_env(char *old_pwd, char *new_pwd, int print_flag)
{
	if (print_flag && new_pwd)
		printf("%s\n", new_pwd);
	set_env("OLDPWD", old_pwd);
	free(old_pwd);
	if (new_pwd)
	{
		set_env("PWD", new_pwd);
		free(new_pwd);
	}
}
