#include "../includes/mini.h"

size_t	count_cmds_tokens(t_input *current_token)
{
	size_t	tokens_count;

	tokens_count = 0;
	while (current_token && current_token->type != TYPE_PIPE)
	{
		if (current_token->type == TYPE_WORD)
			tokens_count++;
		current_token = current_token->next;
	}
	return (tokens_count);
}