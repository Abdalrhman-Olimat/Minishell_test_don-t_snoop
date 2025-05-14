#include "../includes/mini.h"

void	play_after_tokens(t_shell *shell)
{
	char	**args;

	if (!shell || !shell->tokens)
		return ;


	args = tokens_to_array(shell->tokens);
	normalize_linked_list(shell->tokens);
	// printf("Tokens after normalization:\n");
	// print_tokens(shell->tokens); // Printing the Linked List

    // print_tokens(shell->tokens); // Printing only the Linked List
	// print_args(args); // Printing the array of strings		// TEST (1) : Working 100
	if (!args)
	{
		ft_putstr_fd("Unfortunately .. an error occoured -> failed in memory allocation for args\n", 2);
		return ;
	}
	shell->someone.args = args;
	cmds(shell, 1, 0);  // pass shell and args array for execution
	free_token_array(args, count_tokens(shell->tokens));  // cleanup
}