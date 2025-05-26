#include "../includes/mini.h"

bool matches_redirection(const char *token)
{
	return (my_strcmp(token, "<") == 0 || my_strcmp(token, ">") == 0);
}

bool matches_double_redirection(const char *token)
{
	return (my_strcmp(token, "<<") == 0 || my_strcmp(token, ">>") == 0);
}

bool is_pipe_token(const char *token)
{
	return (my_strcmp(token, "|") == 0);
}


