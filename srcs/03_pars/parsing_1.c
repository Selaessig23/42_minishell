/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:11:56 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/19 14:22:20 by mpeshko          ###   ########.fr       */
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

/**
 * @brief this function organises the parsing part
 * (the preparation of command line input for execution)
 * 1st an array of strings (input_arr) is created out of 
 * the readline input (all keywords are seperated here)
 * 2nd the array of strings is trasnformed into a
 * linked list and each node get a token describing
 * the type of the input-keyword
 * 3rd check for syntax errors
 * 4th a linked list for execution is created (ft_commands)
 * 
 * @param input the command line input from readline
 * @param big struct with all necessary information to run a command, 
 * the linked list of commands is saved here
 */
int	minishell_parsing(char *input, t_big *big)
{
	char	**input_arr;
	t_list	*lexx;

	lexx = NULL;
	input_arr = create_cleanarr(&input);
	free(input);
	input = NULL;
	if (!input_arr)
		return (0);
	lexx = ft_tokenizer(input_arr);
	ft_free(input_arr);
	input_arr = NULL;
	if (!lexx || ft_syntax(lexx))
	{
		big->exit_code = 2;
		ft_free_ll(&lexx);
		return (0);
	}
	ft_expa_precond(lexx, big);
	ft_commands(lexx, &big);
	ft_free_ll(&lexx);
	return (1);
}
