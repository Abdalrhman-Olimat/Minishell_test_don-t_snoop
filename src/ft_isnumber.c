#include "../includes/mini.h"

/*
 * Check if a string is a valid number
 * Valid formats: "+123", "-456", "789"
 * Invalid: "12a3", "++123", "--456", " 123", "123 ", etc.
 */
int ft_isnumber(const char *str)
{
    int i;

    if (!str || !*str)
        return (0);

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    
    /* Empty string or just a sign is not a number */
    if (!str[i])
        return (0);

    /* Check that all remaining characters are digits */
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }

    return (1);
}
