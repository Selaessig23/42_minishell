/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:42:56 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/19 10:36:05 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION:
 * in this file the lexing-part of creating the minishell is organised
 * 1st it checks for open pipes (->extra prompt)
 * 2nd it searches for operators (except those in quotes)
 * and adds spaces before and after
 * 3rd it splits the input string from readline into an array of strings
 */
/**
 * @brief a helper function for ft_count,
 * it loops through not necessary parts of a string
 * (within quotes)
 * while continuing counting the indexer
 *
 * @param src the string to loop in
 * @param len the indexer to continue counting while iterating
 * @param endsign the sign until the indexer should jump to
 */
static char	*ft_jumper(char *src, int *len, char endsign)
{
	*len = *len + 1;
	src += 1;
	while (*src && *src != endsign)
	{
		(*len) += 1;
		src += 1;
	}
	return (src);
}

/**
 * @brief function that checks for occurence of unquoted operators
 * and calculates extra memory space (len) for adding spaces in
 * between
 *
 * @param src the string to count in
 */
static int	ft_count(char *src)
{
	int		len;
	char	*temp;

	len = 0;
	temp = src;
	while (*temp)
	{
		if (*temp == '\"')
			temp = ft_jumper(temp, &len, '\"');
		else if (*temp == '\'')
			temp = ft_jumper(temp, &len, '\'');
		if (*temp && *(temp + 1) && double_operator_check(*temp, *(temp + 1)))
		{
			len += 3;
			temp += 1;
		}
		else if (*temp && single_operator_check(*temp))
			len += 2;
		if (*temp)
		{
			len += 1;
			temp += 1;
		}
	}
	return (len);
}

/**
 * @brief function that creates a new cleaned input-string
 * with spaces for and after unquoted operators
 * trim_out_spaces deletes not required spaces (not very important
 * as spaces and tabs will be deleted by split function afterwards anyhow)
 * 
 * @param src the source string to clean
 */
static char	*ft_clean_input(char *src)
{
	char	*dest;
	size_t	len;

	dest = NULL;
	len = ft_count(src);
	if (len == (ft_strlen(src)))
		return (ft_strdup(src));
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
	{
		free(src);
		error_and_exit(2);
	}
	ft_create_clean_input(dest, src);
	trim_out_spaces(&dest);
	return (dest);
}

/**
 * @brief function that organises the splitting of
 * command line input (=string) to an array of strings,
 * separators are tabs, spaces
 * 
 * @param readline_input the genuine command line input string* 
 * @param clean_input the cleaned (prepared) command line input string
 */
static char	**ft_split_rlinput(char **readline_input, char *clean_input)
{
	char	**input_arr;

	input_arr = ft_split_quotes(clean_input, ' ');
	if (!input_arr)
	{
		free(clean_input);
		clean_input = NULL;
		ft_free(readline_input);
		readline_input = NULL;
		error_and_exit(2);
	}
	return (input_arr);
}

/**
 * @brief function that creates an array of strings and organises 
 * the cleaning of command line (according to syntax rules) as well 
 * as checking for extra input in case of incomplete_input (unclosed pipe).
 * 
 * is_incomplete_input - function that handles input with one | in the end.
 *
 * @param readline_input the input of command line read by function readline
 * @return: an array of strings with cleaned command line input
 */
char	**create_cleanarr(char **readline_input)
{
	char	*clean_input;
	char	**input_arr;

	clean_input = NULL;
	input_arr = NULL;
	while (is_incomplete_input(*readline_input))
	{
		if (g_signalnum == 1)
		{
			input_arr = NULL;
			return (input_arr);
		}
		to_complete_input(readline_input);
	}
	clean_input = ft_clean_input(*readline_input);
	if (!clean_input)
	{
		ft_free(readline_input);
		error_and_exit(2);
	}
	input_arr = ft_split_rlinput(readline_input, clean_input);
	free(clean_input);
	clean_input = NULL;
	return (input_arr);
}
