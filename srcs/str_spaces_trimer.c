#include "minishell.h"

/**
 * Counting a new length to allocate memory for the new trimmed string.
 * (c) Maryna
 */
int	count_trim_len(char *str)
{
	char	*temp;
	size_t	new_len;
	int		i;
	int		last;

	temp = str;
	i = 0;
	new_len = 0;
	last = ft_strlen(str) - 1;
	if (last == 0)
		return (1);
	while (temp[i] == 32)
	{
		i++;
		new_len++;
	}
	new_len = ft_strlen(str) - new_len;
	while (temp[last] == 32)
	{
		last--;
		new_len--;
	}
	return (new_len);
}

/**
 * To trim leading and trailing spaces from a string
 * (c) Maryna
 */
void	trim_it(char **str, char **new)
{
	int	last_not_space;
	int	last;
	int	i;
	int	j;

	i = 0;
	j = 0;
	last_not_space = 0;
	last = ft_strlen(*str) - 1;
	while ((*str)[last] == 32)
		last--;
	last_not_space = last;
	while ((*str)[i] == 32)
		i++;
	while (i <= last_not_space)
	{
		(*new)[j] = (*str)[i];
		i++;
		j++;
	}
	(*new)[j] = '\0';
}

/**
 * To trim leading and trailing spaces from a string and then
 * update the original string pointer with the new trimmed string.
 * (c) Marina
 */
void	trim_out_spaces(char **str)
{
	size_t	new_len;
	char	*new;

	new_len = count_trim_len(*str);
	if (new_len == ft_strlen(*str))
		return ;
	new = ft_calloc(new_len + 1, sizeof(char));
	if (!new)
	{
		perror ("ft_calloc error");
		return ;
	}
	trim_it(str, &new);
	free(*str);
	*str = new;
}
