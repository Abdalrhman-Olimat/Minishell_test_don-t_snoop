#include "../includes/mini.h"

char **copy_old_data(int old_len, int new_len, char **old_str)
{
	char **new_str;
	int		i;

	i = -1;
	new_str = malloc(new_len * sizeof(char *));
	if (!new_str)
	{
		free(old_str);
		return (NULL);
	}
	while (++i < old_len)
	{
		new_str[i] = malloc((ft_strlen(old_str[i]) + 1) * sizeof(char));
		if (!old_str[i])
		{
			while (i-- > 0)
				free(new_str[i]);
			free(new_str);
			free(old_str);
			return (NULL);
		}
		ft_strlcpy(new_str[i], old_str[i], ft_strlen(old_str[i]) + 1);
	}
	free_2d_arr(old_str);
	return (new_str);
}