#include "../includes/mini.h"

void normalize_linked_list(t_input *head)
{
    if (!head)
        return;
        
    while (head)
    {
        if (head->string && head->string[0] == ' ' && head->string[1] != '\0')
        {
            char *new_str = ft_strdup(head->string + 1);
            if (new_str)
            {
                free(head->string);
                head->string = new_str;
            }
            // If strdup fails, we keep the original string - don't leave it NULL
        }
        // Handle empty strings to avoid later issues
        else if (head->string && head->string[0] == '\0')
        {
            // Replace with a single space to ensure it's not an empty string
            free(head->string);
            head->string = ft_strdup(" ");
        }
        head = head->next;
    }
}

/*
void remove_spaces(char *str)
{
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
}
*/