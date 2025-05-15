#include "../includes/mini.h"

t_shell_returns	cmds(t_shell *shell, int i, int j) // i = 1, j = 0
{
	shell->cmds = big_malloc(shell, -1);
	if (!shell || !shell->cmds)
		return (SHELL_FAILURE);

	// input_handler(shell, 0, 1);	// do expands and split & more 
	analyze_pipes(shell, 0 , 0);
	// analyze_cmds(shell, 0 , 0); // Currently not used or needed; delete file later
	// process_cmds(shell, 0 , 1);




	// Optionally: You can process commands here if needed
	// some_operations_calcs(shell);
	// if (shell->analyzing_data.dirs_num > 0 && redirs_playpool(shell))	// dir & process_redirs
		// return (handle_failure(shell, 2, "Redirection failed"));
	// if (!analyze_quotes(shell))
		// return (handle_failure(shell, 2, "Unmatched quotes"));

	// if (!check_pipe_operate(shell))
	// 	return (handle_failure(shell, 2, "Pipe syntax error"));
	// execute(shell);
	// clean_all(shell);
	return (i);
}