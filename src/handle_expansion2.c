#include "../includes/mini.h"

char **allocate_expanded_args(char **original, char **suffix, int skip)
{
	int original_len;
	int suffix_len;

	original_len = get_2d_len(original);
	suffix_len = get_2d_len(suffix) - skip;
	return (realloc_2d_appending(original, 
			original_len, original_len + suffix_len));
}

int copy_suffix(char **args, char **suffix, int start_index, int skip)
{
	int i;
	int j;
	
	i = start_index;
	j = skip;
	while (suffix[j])
	{
		args[i] = ft_strdup(suffix[j]);
		if (!args[i])
			return (0);
		i++;
		j++;
	}
	args[i] = NULL;
	return (1);
}