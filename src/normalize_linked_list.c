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
        ft_strtrim(head->string, " \t\n\r\v\f");
        head = head->next;
    }
}
