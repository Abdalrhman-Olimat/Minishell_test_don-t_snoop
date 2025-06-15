#include "../includes/mini.h"

/*
 * Checks if the character is a valid identifier character (alphanumeric or '_')
 */
int	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
 * Checks if the first character of the identifier is valid (alphabet or underscore)
 */
int	is_valid_first_char(const char first_char)
{
	return (ft_isalpha(first_char) || first_char == '_');
}


/*
 * Loops over the string until '=' or '\0' and checks if the characters are valid
 */
int	is_valid_until_equal_or_end(const char *str, int start_index)
{
	int	i;

	i = start_index;
	while (str[i] && str[i] != '=')
	{
		if (!is_valid_char(str[i]))  // Use the new helper function for validation
			return (0);
		i++;
	}
	return (1);
}

/*
 * Checks if the given identifier is valid
 */
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);

	if (!is_valid_first_char(str[0]))    // Check the first character
		return (0);
	
	i = 1;
	return (is_valid_until_equal_or_end(str, i));  // Use the helper to check the rest of the string
}
