/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:24:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/02/11 11:42:53 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*int main()
{
char *input;

while ((input = readline("minishell>")) != NULL)
{
    if (*input)
    {
        printf("You entered: %s\n", input);
    }
    free(input);
}
return 0;

}*/



// Get input from the user
char *get_input(void) {
    char *input = readline(NULL);
    if (input == NULL) {
        printf("exit\n");
        exit(0);
    }
    add_history(input);
    return input;
}

int main() {


    // Main loop
    while (1) {
        printf("minishell> ");    // Display prompt
        char *input = get_input();
        if (ft_strlen(input) > 0)
        {  // Process only non-empty input
            printf("You entered: %s\n", input);
            // Future: Tokenize input here
        }
        free(input);              // Clean up memory
    }
    return 0;
}