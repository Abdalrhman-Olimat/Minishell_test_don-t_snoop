#include "../includes/mini.h"


/*norm and nono function*/
t_input *create_node(char *str, int type)
{
    t_input *new_node = malloc(sizeof(t_input));
    if (!new_node)
        return NULL;
    new_node->string = ft_strdup(str);
    if (!new_node->string) {
        free(new_node);
        return NULL;
    }
    new_node->type = type;
    new_node->next = NULL;
    return new_node;
}

void append_node(t_input **head, char *str, int type)
{
    t_input *new_node = create_node(str, type);
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    if (!*head)
    {
        *head = new_node;
        return;
    }
    t_input *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void free_list(t_input *head)
{
    t_input *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->string);
        free(tmp);
    }
}
void print_tokens(t_input *head)
{
    t_input *tmp = head;
    while (tmp)
    {
        printf("Token: %s, Type: %d\n", tmp->string, tmp->type);
        tmp = tmp->next;
    }
}
