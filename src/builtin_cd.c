/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:16:20 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 03:27:40 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*get_env(const char *name)
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

int	set_env(const char *name, const char *value)
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

/*
int	main(int argc, char *argv[])
{
	char	*no_args[];
	char	*valid_dir[];
	char	*cd_dash[];
	char	*invalid_dir[];

    // Test 1: No argument should take us to HOME
    printf("Testing cd with no argument (should go to HOME):\n");
    no_args[] = { "cd", NULL };
    ft_cd(no_args);
    // Test 2: cd to a valid directory
    printf("\nTesting cd with a valid directory (/tmp):\n");
    valid_dir[] = { "cd", "/tmp", NULL };
    ft_cd(valid_dir);
    // Test 3: cd to OLDPWD (using -)
    printf("\nTesting cd with - (should go to OLDPWD):\n");
    cd_dash[] = { "cd", "-", NULL };
    ft_cd(cd_dash);
    // Test 4: cd with a non-existent directory (should print error)
    printf("\nTesting cd with a non-existent directory (/nonexistentdir):\n");
    invalid_dir[] = { "cd", "/nonexistentdir", NULL };
    ft_cd(invalid_dir);
    return (0);
}
*/