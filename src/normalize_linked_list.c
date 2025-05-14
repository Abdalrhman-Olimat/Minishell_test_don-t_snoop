#include "../includes/mini.h"

static void remove_spaces(char *str)
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
        remove_spaces(head->string);
        head = head->next;
    }
}
