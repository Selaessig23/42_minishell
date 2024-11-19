/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:36:27 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 10:36:32 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION: 
 * Modified ft_split-function to exclude text in quotes from
 * splitting string by using a delimiter. 
 * What is more, it also considers spaces / tabs/ newlines
 * 
 * RETURN VALUE:
 * The array of new strings resulting from the split.
 * NULL if the allocation fails.
 */

/** 
 * @brief function to free the first arrno number of strings 
 * of an array of strings
 * 
 * @param dest the array of char that should be freed
 * @param arrno the index until the array of char has to be freed
 */
static void	*ft_free_i(char **dest, int arrno)
{
	int	i;

	i = 0;
	while (i <= arrno)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return (0);
}

/**
 * @brief function that writes new strings to the
 * (aleady malloced) array of strings
 * 
 * @param dest the array of strings to write to
 * @param s the string to copy from
 * @param c the char that serves as separator for splitting s
 * @param i the index to start from reading (and copying) from s
 */
static char	**ft_strcut(char **dest, const char *s, char c, size_t i)
{
	size_t	a;
	size_t	p;

	a = 0;
	p = i;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			i = ft_quo_handling(s, i);
		if (s[i] == c || is_tab(s[i]) || ((i == ft_strlen(s) - 1) && s[i] != c))
		{
			if ((i == ft_strlen(s) - 1) && s[i] != c)
				dest[a] = ft_substr(s, p, (i + 1 - p));
			else
				dest[a] = ft_substr(s, p, (i - p));
			if (!(dest[a]))
				return (ft_free_i(dest, a));
			i = (ft_space_tab_jump(s, c, (i + 1)) - 1);
			p = i + 1;
			a++;
		}
		i++;
	}
	dest[a] = NULL;
	return (dest);
}

/**
 * @brief this function counts occurance of c & tabs in s
 * respecitive how many strings have to been created for
 * required array of strings
 * 
 * @param i starting index for string s
 * @param s the string in which occurance of c has to be counted
 * @param c the char to search and count for in s
 */
static size_t	ft_amc(size_t i, const char *s, char c)
{
	size_t	amountc;

	amountc = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			i = ft_quo_handling(s, i);
		else if (s[i] == c || is_tab(s[i]))
		{
			amountc++;
			i = (ft_space_tab_jump(s, c, (i + 1)) - 1);
		}
		i++;
	}
	if (s[i - 1] != c)
		return (amountc + 1);
	else
		return (amountc);
}

/**
 * @brief function to organise malloc of return value char **
 * and content generation for return value (splitting s if c or tab)
 * 
 * @param s the input string to split
 * @param c the delimiter used for splitting
 */
char	**ft_split_quotes(char const *s, char c)
{
	char	**dest;
	size_t	len;
	size_t	i;

	i = 0;
	i = ft_space_tab_jump(s, c, i);
	if (ft_strncmp(s, "", 1) == 0)
	{
		dest = ft_calloc(1, sizeof(char *));
		if (!dest)
			return (NULL);
	}
	else
	{
		len = ft_amc(i, s, c);
		dest = ft_calloc((len + 1), sizeof(char *));
		if (!dest)
			return (NULL);
		dest = ft_strcut(dest, s, c, i);
	}
	return (dest);
}
