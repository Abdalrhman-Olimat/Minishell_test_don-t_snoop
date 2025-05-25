#include "../includes/mini.h"

char **allocate_expanded_args(char **original, char **suffix, int skip)
{
	int original_len;
	int suffix_len;

	original_len = get_2d_len(original);
	suffix_len = get_2d_len(suffix) - skip;
	return (realloc_2d_appending(original, 
			original_len, (original_len + suffix_len)));
}

static int copy_one_by_one(char **dst, char **src, int *dst_i, int *src_i)
{
	while (src[*src_i])
	{
		dst[*dst_i] = ft_strdup(src[*src_i]);
		if (!dst[*dst_i])
			return (0);
		(*dst_i)++;
		(*src_i)++;
	}
	dst[*dst_i] = NULL;
	return (1);
}

int copy_suffix(char **args, char **suffix, int start_idx, int skip_idx)
{
	int i;
	int j;

	i = start_idx;
	j = skip_idx;
	return (copy_one_by_one(args, suffix, &i, &j));
}

/*
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
*/