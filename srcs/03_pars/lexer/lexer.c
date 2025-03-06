/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:11:56 by mstracke          #+#    #+#             */
/*   Updated: 2025/03/06 10:50:15 by mstracke         ###   ########.fr       */
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
 * @param src the source string to clean (from command line | readline input)
 */
static char	*ft_clean_input(t_big *big, char *src)
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
		error_and_exit(2, big);
	}
	ft_create_clean_input(dest, src);
	trim_out_spaces(big, src, &dest);
	return (dest);
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
char	**create_cleanarr(t_big *big, char **readline_input)
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
		to_complete_input(big, readline_input);
	}
	clean_input = ft_clean_input(big, *readline_input);
	if (!clean_input)
	{
		ft_free(readline_input);
		error_and_exit(2, NULL);
	}
	input_arr = ft_split_rlinput(big, readline_input, clean_input);
	free(clean_input);
	clean_input = NULL;
	return (input_arr);
}
