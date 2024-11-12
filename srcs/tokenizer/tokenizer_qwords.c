/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_qwords.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:22:33 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 12:22:53 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the special treatment of qwords (token 25 | 26) is organised
 * qwords are cases like
 * "argument1"withoutspaceafterquotes or
 * argument1"withoutspace"afterquotes..
 * 'argument1'withoutspaceafterquotes or
 * argument1'withoutspace'afterquotes...
 * these cases have to be checked for unquoted strings (token 27 / 28)
 */ 

/**
 * functin to set a value to its default value in case of condition == true
 * 
 * @param value_default value to use for overwriting
 * @param value_reset value to overwrite
 * @param condition condition to check
 */
static char	*ft_setdefault(char **value_default, 
				char **value_reset, bool condition)
{
	if (condition == true)
		*value_reset = *value_default;
	return (NULL);
}

/**
 * @helper function for ft_qword_quotecheck which returns the pointer 
 * to part of string after second "\'" if token == 26 or
 * pointer to part of string after second "\"" if token == 25 or 
 * pointer to part of string after second quote (depends 
 * on which kind of quote comes first in string) if there is no exact
 * information about the token (=0) 
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 * @param token the token of the input string that has to be checked
 * @param returner a bool variable which sets input_string to its original value
 * if value is set on true, this helps to use the function only for checks (true)
 * but also for overwriting (false)
 */
static char	*ft_get_quotendpointer(char *input_string, 
			t_tokentype token, bool returner)
{
	int		i;
	char	countsign;
	char	*input_string_copy;

	i = 0;
	input_string_copy = input_string;
	if (token == 25)
		countsign = '\"';
	else if (token == 26)
		countsign = '\'';
	else if (!ft_check_fstquote(input_string, '\"'))
		countsign = '\"';
	else
		countsign = '\'';
	while (*input_string && i <= 1)
	{
		if (*input_string == countsign)
			i += 1;
		input_string += 1;
	}
	if (i <= 1)
		return (ft_setdefault(&input_string_copy, &input_string, returner));
	else
		return (input_string);
}

/**
 * @brief function to handle a special case
 * of command line input in token 
 * D_Q_WORD = 25, e. g. "argument1"withoutspaceafter"quotes''""
 * S_Q_WORD = 26, // e. g. argument1'withoutspace'afterquotes'"'"...
 * if any of this tokens end up with an unequal number of quotes
 * (whether single or double) they have to be handled as 
 * cases with unclosed qoutation marks
 * 
 * function ft_check_fstquote in file tokenizer_utils.c
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 * @param token_old the token that has to be checked for
 */
void	ft_qword_quotecheck(char *input_string, t_tokentype *token_old)
{
	int		count_squote;
	int		count_dquote;
	char	*input_string_copy;
	int		i;

	count_squote = 0;
	count_dquote = 0;
	i = 0;
	input_string_copy = input_string;
	while (*input_string_copy 
		&& (ft_get_quotendpointer(input_string_copy, 0, true) != NULL))
		input_string_copy = ft_get_quotendpointer(input_string_copy, 0, 0);
	while (input_string_copy[i])
	{
		if (input_string_copy[i] == '\'')
			count_squote += 1; 
		else if (input_string_copy[i] == '\"')
			count_dquote += 1;
		i += 1;
	}
	if (count_squote != 0 && (count_squote % 2 != 0) 
		&& (!ft_check_fstquote(input_string_copy, '\'')))
		*token_old = 28;
	else if (count_dquote != 0 && (count_dquote % 2 != 0))
		*token_old = 27;
}
