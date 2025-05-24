#include "../includes/mini.h"

static t_input *copy_of_tokens(t_shell *shell, t_input *head)
{
	t_input *new_tokens;
	t_input *current_node;
	t_input *last_new;
	t_input *new_node;

	new_tokens = NULL;
	last_new = NULL;

	if (shell == NULL || head == NULL)
		return (NULL);

	current_node = head;
	while (current_node != NULL)
	{
		new_node = (t_input *)malloc(sizeof(t_input));
		if (new_node == NULL)
		{
			while (new_tokens != NULL)
			{
				t_input *tmp = new_tokens;
				new_tokens = new_tokens->next;
				free(tmp->string);
				free(tmp);
			}
			return (NULL);
		}
		if (current_node->string != NULL)
			new_node->string = strdup(current_node->string);
		else
			new_node->string = NULL;
		new_node->type = current_node->type;
		new_node->next = NULL;

		if (new_tokens == NULL)
			new_tokens = new_node;
		else
			last_new->next = new_node;

		last_new = new_node;
		current_node = current_node->next;
	}
	return (new_tokens);
}

void	play_after_tokens(t_shell *shell)
{
	char	**args;

	if (!shell || !shell->tokens)
		return ;


	args = tokens_to_array(shell->tokens);
	normalize_linked_list(shell->tokens);
	shell->tokens_header = copy_of_tokens(shell, shell->tokens); // Copying the tokens to a new linked list
	// printf("Tokens after normalization:\n");
	// print_tokens(shell->tokens); // Printing the Linked List

    // print_tokens(shell->tokens); // Printing only the Linked List
	// print_args(args); // Printing the array of strings		// TEST (1) : Working 100
	if (!args)
	{
		ft_putstr_fd("Unfortunately .. an error occoured -> failed in memory allocation for args\n", 2);
		return ;
	}
	shell->analyzing_data.args = args;
	cmds(shell, 1, 0);  // pass shell and args array for execution
	// free_token_array(args, count_tokens(shell->tokens));  // cleanup
}