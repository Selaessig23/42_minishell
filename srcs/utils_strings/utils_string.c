/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:29:49 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/19 14:42:04 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function counts a number of strings in array of strings.
 * It serves for memory allocation for an array of strings.
*/
int	count_strings(char **envp)
{
	int	i;

	i = 0;
	while (*envp)
	{
		i++;
		envp++;
	}
	return (i);
}

/**
 * This function frees an array of strings.
 * The function iterates through each string in the array, freeing each one 
 * individually. After freeing all the strings, it frees the array itself.
 */
void	ft_freestr(char **lst)
{
	int		i;
	char	*n1;

	i = 0;
	if (!lst)
		return ;
	while (lst[i] != NULL)
	{
		n1 = lst[i];
		i++;
		free(n1);
	}
	free(lst);
}

/* Like the strncmp() function, but compares entire strings, no need to pass
a size.
-	If the two strings are identical, the function returns 0, indicating
	no difference.
-	If a difference is found, and the first differing character in the second
	string (s2) is greater than the character at the same position in the first
	string (s1), the result is negative.
-	If the first differing character in s2 is less than the character at the
	same position in s1, the result is positive.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_last_char(const char *str, char c)
{
	size_t	len;

	len = 0;
	if (!str || *str == '\0')
		return (0);
	len = ft_strlen(str);
	if (str[len - 1] == c)
		return (1);
	else
		return (0);
}

int	is_exact_string(const char *str_org, char *str_cmp)
{
	if (!ft_strncmp(str_org, str_cmp, ft_strlen(str_org)) 
		&& ft_strlen(str_org) == ft_strlen(str_cmp))
		return (1);
	else
		return (0);
}
