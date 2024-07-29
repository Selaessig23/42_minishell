/**
 * DESCRIPTION: 
 * Modified ft_spilt-function to exclude text in quotes from
 * splitting string by using a delimiter. 
 * What is more, it also considers spaces / tabs/ newlines
 * 
 * The array must end with a NULL pointer 
 * and considers edge cases << and >>. 
 * 
 * RETURN VALUE:
 * The array of new strings resulting from the split.
 * NULL if the allocation fails.
 */

#include "minishell.h"

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
 * @brief function that iterates s if spaces (= c) || tabs
 * 
 * @param s string to search in
 * @param c char to search for (beside tabs)
 * @param i the index to start iterating from
 */
static int	ft_space_tab_jump(const char *s, char c, int i)
{
	while (s[i] && (s[i] == c 
			|| (s[i] >= 9 && s[i] <= 13)))
		i++;
	return (i);
}

/**
 * @brief function to exclude content within quotation marks from splitting
 * 
 * @param s string to search in for quotation marks
 * @param i the index to start searching
 */
static int	ft_quo_handling(const char *s, int i)
{
	if (s[i] == '\'')
	{
		if (s[i + 1] != '\0')
			i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	else if (s[i] == '\"')
	{
		if (s[i + 1] != '\0')
			i++;
		while (s[i] && s[i] != '\"')
			i++;
	}
	if (s[i] == '\0')
		i--;
	return (i);
}

/**
 * @brief 
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
		if (s[i] == c || ((i == ft_strlen(s) - 1) && s[i] != c))
		{
			if ((i == ft_strlen(s) - 1) && s[i] != c)
				dest[a] = ft_substr(s, p, (i + 1 - p));
			else
				dest[a] = ft_substr(s, p, (i - p));
			if (!(dest[a]))
				return (ft_free_i(dest, a));
			//if we have to adapt this loop to ignore spaces and tabs 
			//between tokens and at the end of input-string
			i = (ft_space_tab_jump(s, c, (i + 1)) - 1);
			// while (s[i + 1] == c)
			// 	i++;
			p = i + 1;
			a++;
		}
		i++;
	}
	dest[a] = NULL;
	return (dest);
}

/**
 * @brief this function counts occurance of c in s
 * respecitive how many words have to been created
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
		else if (s[i] == c)
		{
			amountc++;
			//if we have to adapt this loop to ignore spaces and tabs 
			//between tokens and at the end of input-string
			i = (ft_space_tab_jump(s, c, (i + 1)) - 1);
			// while (s[i + 1] == c)
			// 	i++;
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
 * and content generation for return value (splitting s if c)
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
	//if we have to adapt this loop to ignore spaces and tabs 
	//at the beginning of input-string
	i = ft_space_tab_jump(s, c, i);
	// while (s[i] == c)
	// 	i++;
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
