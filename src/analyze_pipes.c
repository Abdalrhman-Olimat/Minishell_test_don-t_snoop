#include "../includes/mini.h"

int	analyze_pipes(t_shell *shell, int i, int j)
{
    char	c;
    t_quote_state quote_state;
    char	*arg;

    if (!shell || !shell->middle_some.args)
        return (0);

    i = 0;
    quote_state = QUOTE_NONE;
    shell->analyzing_data.pipe_count = 0;

    // Iterate through each argument in args
    while (shell->middle_some.args[i])
    {
        arg = shell->middle_some.args[i];
        j = 0;

        // Iterate through each character of the current argument
        while ((c = arg[j++]))
        {
            // Handle quote state changes
            if (c == '\'' && quote_state == QUOTE_NONE)
                quote_state = QUOTE_SINGLE;
            else if (c == '\'' && quote_state == QUOTE_SINGLE)
                quote_state = QUOTE_NONE;

            if (c == '"' && quote_state == QUOTE_NONE)
                quote_state = QUOTE_DOUBLE;
            else if (c == '"' && quote_state == QUOTE_DOUBLE)
                quote_state = QUOTE_NONE;

            if (c == '`' && quote_state == QUOTE_NONE)
                quote_state = QUOTE_BACKTICK;
            else if (c == '`' && quote_state == QUOTE_BACKTICK)
                quote_state = QUOTE_NONE;

            // Count pipes only outside quotes
            if (c == '|' && quote_state == QUOTE_NONE)
                shell->analyzing_data.pipe_count++;
        }
        i++; // Move to next argument
    }
    // printf("Pipe counted! Total pipe count: %d\n", shell->analyzing_data->pipe_count);  // TEST (2) - Worked 
    return (1);
}