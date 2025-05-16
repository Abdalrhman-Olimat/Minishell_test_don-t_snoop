#include "../includes/mini.h"

static int analyze_main(char c, t_quote_state *quote_state)
{
    if (c == '\'' && *quote_state == QUOTE_NONE)
        *quote_state = QUOTE_SINGLE;
    else if (c == '\'' && *quote_state == QUOTE_SINGLE)
        *quote_state = QUOTE_NONE;

    if (c == '"' && *quote_state == QUOTE_NONE)
        *quote_state = QUOTE_DOUBLE;
    else if (c == '"' && *quote_state == QUOTE_DOUBLE)
        *quote_state = QUOTE_NONE;

    if (c == '`' && *quote_state == QUOTE_NONE)
        *quote_state = QUOTE_BACKTICK;
    else if (c == '`' && *quote_state == QUOTE_BACKTICK)
        *quote_state = QUOTE_NONE;

    return (*quote_state);
}


int	analyze_pipes(t_shell *shell, int i, int j)
{
    char	c;
    t_quote_state quote_state;
    char	*arg;

    if (!shell || !shell->analyzing_data.args)
        return (0);

    i = 0;
    quote_state = QUOTE_NONE;
    shell->analyzing_data.pipe_count = 0;

    while (shell->analyzing_data.args[i])
    {
        arg = shell->analyzing_data.args[i];
        j = 0;
        while ((c = arg[j++]))
        {
            analyze_main(c, &quote_state);
            if (c == '|' && quote_state == QUOTE_NONE)
                shell->analyzing_data.pipe_count++;
        }
        i++;
    }
    return (1);
}