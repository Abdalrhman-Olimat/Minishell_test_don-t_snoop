#include "../includes/mini.h"


void expander1(t_input *tokens)
{
    t_input *tmp = tokens;
    while (tmp)
    {
        if (tmp->type == TYPE_WORD)
        {
            
        }
        else
        {
            printf("Not expanding: %s\n", tmp->string);
        }
        tmp = tmp->next;
    }
}