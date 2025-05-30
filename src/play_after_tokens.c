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
			free_list(new_tokens); // Using the existing free_list function
			return (NULL);
		}
		
		// Initialize with zeros to avoid uninitialized memory
		ft_memset(new_node, 0, sizeof(t_input));
		
		if (current_node->string != NULL)
		{
			new_node->string = ft_strdup(current_node->string);
			if (!new_node->string)
			{
				free(new_node);
				free_list(new_tokens);
				return (NULL);
			}
		}
		else
			new_node->string = NULL;
			
		new_node->type = current_node->type;
		new_node->flags = current_node->flags; // Copy the flags too
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
	t_shell_returns result;

	if (!shell || !shell->tokens)
		return ;
	args = tokens_to_array(shell->tokens);
	normalize_linked_list(shell->tokens);
	shell->tokens_header = copy_of_tokens(shell, shell->tokens); // Copying the tokens to a new linked list
	
	if (!args)
	{
		ft_putstr_fd("Unfortunately .. an error occoured -> failed in memory allocation for args\n", 2);
		if (shell->tokens_header)
		{
			free_list(shell->tokens_header);
			shell->tokens_header = NULL;
		}
		return ;
	}
	
	shell->analyzing_data.args = args;
	result = cmds(shell, 1, 0);  // pass shell and args array for execution
	
	// Free the args array - use tokens_header for count to ensure proper cleanup
	if (shell->analyzing_data.args && shell->tokens_header)
	{
		int token_count = count_tokens(shell->tokens_header);
		free_token_array(shell->analyzing_data.args, token_count);
		shell->analyzing_data.args = NULL;
	}
	else if (shell->analyzing_data.args)
	{
		// Fallback if tokens_header is NULL but args still exists
		free(shell->analyzing_data.args);
		shell->analyzing_data.args = NULL;
	}
	
	// Free any possible expanded strings created during token processing
	if (shell->tokens)
	{
		t_input *current = shell->tokens;
		while (current)
		{
			if (current->string && current->string[0] == '\0')
			{
				// Replace empty strings with NULL to avoid double-free issues
				free(current->string);
				current->string = NULL;
			}
			current = current->next;
		}
	}
	
	// Free command structures if they exist and weren't freed by cmds
	if (shell->cmds && shell->analyzing_data.cmds_count > 0)
	{
		free_cmds_all(shell->cmds, shell->analyzing_data.cmds_count, 0);
		shell->cmds = NULL;
	}
}
