#include "../includes/mini.h"

void advanced_symbols_check(t_shell *shell, t_input **tokens, int *itereator_of_cmd)
{
	if (!(*tokens)->next || (*tokens)->next->type != TYPE_WORD)
	{
		shell->cmds[*itereator_of_cmd]->skip_cmd = true;
		shell->exit_status = 2;
	}
}