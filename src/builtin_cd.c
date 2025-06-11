/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:15:28 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/11 15:48:02 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char	*get_cd_target_directory(char **argv, char *old_pwd,
		int *print_flag)
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
		return (target_dir);
	}
	return (handle_cd_special_args(argv, old_pwd, print_flag));
}

static void	update_pwd_environment(char *old_pwd, char *new_pwd, int print_flag)
{
	if (!new_pwd)
		perror("cd: getcwd failed");
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

static char	*handle_cd_special_args(char **argv, char *old_pwd, int *print_flag)
{
	char	*target_dir;

	if (argv[2] != NULL)
	{
		fprintf(stderr, "cd: too many arguments\n");
		free(old_pwd);
		return (NULL);
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		target_dir = get_env("OLDPWD");
		if (!target_dir)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			free(old_pwd);
			return (NULL);
		}
		*print_flag = 1;
		return (target_dir);
	}
	return (argv[1]);
}

int	ft_cd(char **argv)
{
	char	*target_dir;
	char	*old_pwd;
	char	*new_pwd;
	int		print_flag;

	print_flag = 0;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("cd: getcwd failed");
		return (1);
	}
	target_dir = get_cd_target_directory(argv, old_pwd, &print_flag);
	if (!target_dir)
		return (1);
	if (chdir(target_dir) != 0)
	{
		fprintf(stderr, "cd: %s: %s\n", target_dir, strerror(errno));
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	update_pwd_environment(old_pwd, new_pwd, print_flag);
	return (0);
}
