/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:16:20 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:00:37 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*get_env22(const char *name)
{
	extern char	**environ;
	size_t		name_len;
	int			i;

	i = 0;
	name_len = strlen(name);
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, name_len) == 0
			&& environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

int	set_env22(const char *name, const char *value)
{
	if (setenv(name, value, 1) != 0)
	{
		perror("setenv");
		return (1);
	}
	return (0);
}

char	*handle_cd_dash(char *old_pwd, int *print_flag)
{
	char	*target_dir;

	target_dir = get_env22("OLDPWD");
	if (!target_dir)
	{
		fprintf(stderr, "cd: OLDPWD not set\n");
		free(old_pwd);
		return (NULL);
	}
	*print_flag = 1;
	return (target_dir);
}

static int	change_directory(const char *target_dir, char *old_pwd)
{
	if (!target_dir)
		return (1);
	if (chdir(target_dir) != 0)
	{
		fprintf(stderr, "cd: %s: %s\n", target_dir, strerror(errno));
		free(old_pwd);
		return (1);
	}
	return (0);
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
	target_dir = determine_target_dir(argv, old_pwd, &print_flag);
	if (change_directory(target_dir, old_pwd))
		return (1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		perror("cd: getcwd failed");
	update_pwd_env(old_pwd, new_pwd, print_flag);
	return (0);
}
