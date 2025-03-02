#include "../includes/mini.h"

/*norm and nono function*/

t_input *tokenizer(char *input, int len)
{
    t_input *head = NULL;
    int i = 0;
    char token_buf[len + 1];  // Maximum token size is the full input length.
    int token_index = 0;
    
    while (i < len)
    {
        // Skip whitespace; flush token buffer if needed.
        if (input[i] == ' ' || input[i] == '\t')
        {
            if (token_index > 0)
            {
                token_buf[token_index] = '\0';
                append_node(&head, token_buf, TYPE_WORD);
                token_index = 0;
            }
            i++;
            continue;
        }
        
        // Handle metacharacters if we're not building a token.
        if ((input[i] == '|' || input[i] == '<' || input[i] == '>') && token_index == 0)
        {
            if (input[i] == '<' && (i + 1 < len && input[i + 1] == '<')) {
                append_node(&head, "<<", TYPE_HEREDOC);
                i += 2;
                continue;
            }
            if (input[i] == '>' && (i + 1 < len && input[i + 1] == '>')) {
                append_node(&head, ">>", TYPE_APPEND);
                i += 2;
                continue;
            }
            if (input[i] == '|') {
                append_node(&head, "|", TYPE_PIPE);
                i++;
                continue;
            }
            if (input[i] == '<') {
                append_node(&head, "<", TYPE_REDIR_IN);
                i++;
                continue;
            }
            if (input[i] == '>') {
                append_node(&head, ">", TYPE_REDIR_OUT);
                i++;
                continue;
            }
        }
        
        // Handle quotes: include the quotes in the token.
        if (input[i] == '\'' || input[i] == '\"') {
            char quote = input[i];
            // Flush any token in progress.
            if (token_index > 0) {
                token_buf[token_index] = '\0';
                append_node(&head, token_buf, TYPE_WORD);
                token_index = 0;
            }
            char quoted_buf[len + 1];
            int qindex = 0;
            // Copy the opening quote.
            quoted_buf[qindex++] = input[i++];
            // Copy everything until the matching closing quote.
            while (i < len && input[i] != quote) {
                quoted_buf[qindex++] = input[i++];
            }
            // If matching quote found, copy it.
            if (i < len && input[i] == quote)
                quoted_buf[qindex++] = input[i++];
            else {
                fprintf(stderr, "Error: Unclosed quote\n");
                break;
            }
            quoted_buf[qindex] = '\0';
            append_node(&head, quoted_buf, TYPE_WORD);
            continue;
        }
        
        // Otherwise, accumulate the character in the token buffer.
        token_buf[token_index++] = input[i++];
    }
    
    // Flush any remaining token in the buffer.
    if (token_index > 0) {
        token_buf[token_index] = '\0';
        append_node(&head, token_buf, TYPE_WORD);
    }
    
    return head;
}
