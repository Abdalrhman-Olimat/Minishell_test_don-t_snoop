#include "../includes/mini.h"

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

void normalize_linked_list(t_input *head)
{
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
        }
        head = head->next;
    }
}
