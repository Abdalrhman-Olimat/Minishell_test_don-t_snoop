#include "../includes/mini.h"

// int cmds(t_shell *shell, int i, int j); // i = 1, j = 0

t_shell_returns	cmds(t_shell *shell, int i, int j) // i = 1, j = 0
{
    t_input *tokens_head;

	analyze_pipes(shell, 0 , j);
	shell->cmds = big_malloc(shell, -1);
	if (!shell || !shell->cmds)
		return (SHELL_FAILURE);

	// input_handler(shell, 0, 1);	// do expands and split & more 
	// analyze_cmds(shell, 0 , 0); // Currently not used or needed; delete file later
	i = FT;
	if (i > 0)
	 {
		 if (!parse_tokens_into_cmds(shell, &tokens_head, 0 , i))
		 {
			 free_big_malloc_cmds(0, shell->cmds, -1);
			 return (SHELL_FAILURE);
		 }
		 if (shell->cmds)
			 if (!execute_here_doc(shell, -1, 0, FT))
			 {
				 shell->exit_status = 130;
				 // TODO - Free tokens Linked List
				 return SHELL_EXIT;
			 }

	 }

	init_splits(shell, 0, 0);
	// TODO- Free all Tokens; bec. not needed now ....
	execute_cmds(shell, -1, 0);








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