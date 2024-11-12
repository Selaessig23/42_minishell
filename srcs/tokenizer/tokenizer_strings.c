/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_strings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:39:29 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 11:39:32 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the cleaned input and by delimiters separated array of strings
 * will be checked for all kinds of string definitions (tokens => 20). 
 * On basis of that, specific tokens will be added.
 * 
 * WORD = 20
 * D_QUOTED = 21 ("hi double quoted")
 * S_QUOTED = 22 ('hi single quoted')
 * D_QUOTED_F = 23 ("hi double unquoted)
 * S_QUOTED_F = 24 ('hi single unquoted)
 * D_Q_WORD = 25 ("argument1"withoutspaceafterquotes or
 * argument1"withoutspace"afterquotes..)
 * S_Q_WORD = 26 ('argument1'withoutspaceafterquotes or
 * argument1'withoutspace'afterquotes...)
 * D_Q_WORD_F = 27 ("argument1'UNCLOSED"'withoutspace"after"quotes or
 * argument1"'UNCLOSED'withoutspace"'after'"quotes...)
 * S_Q_WORD_F = 28 ('argument1'"UNCLOSED"'withoutspaceafterquotes or
 * argument1'"UNCLOSED"withoutspace'"after"'quotes...)
 */

/**
 * @brief function to check the occurance of char checker in string
 * variable checker (== "\'" || "\"")
 * 
 * @param content the string to search in
 * @param checker the char to search for
 * 
 * @return returns 0 if checker char is not 1st quotation found
 */
static int	ft_check_totalchar(char *content, char checker)
{
	int		i;

	i = 0;
	if (ft_check_fstquote(content, checker))
		return (-1);
	while (*content)
	{
		if (*content == checker)
			i++;
		content++;
	}
	return (i);
}

/**
 * @brief helper function for ft_creat_str_token, 
 * that checks if last character of string content
 * is equal to variable checker (== "\'" || "\"")
 * 
 * @param content the string to seach in
 * @param checker the char to search for
 */
static bool	ft_check_lastchar(char *content, char checker)
{
	if (content[ft_strlen(content) - 1] == checker)
		return (0);
	else
		return (1);
}

/**
 * @brief function to check for double quotes and assign
 * a specific value (token) in that case
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input 
 */
static t_tokentype	ft_creat_dquoted_token(char *input_string)
{
	if (!ft_strncmp(input_string, "\"", 1)
		&& ft_check_totalchar(input_string, '\"') == 2
		&& !ft_check_lastchar(input_string, '\"'))
		return (21);
	else if (ft_check_totalchar(input_string, '\"') >= 2)
		return (25);
	else if (!ft_strncmp(input_string, "\"", 1)
		&& ft_check_lastchar(input_string, '\"'))
		return (23);
	else if (ft_check_totalchar(input_string, '\"') == 1)
		return (27);
	else 
		return (0);
}

/**
 * @brief  function to initiate variable token of linked list lexx,
 * here: alls kinds of strings with special focus on single quoted,
 * else: double_quoted_check, else token = word
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 */
t_tokentype	ft_creat_str_token(char *input_string)
{
	if (!ft_strncmp(input_string, "\'", 1)
		&& ft_check_totalchar(input_string, '\'') == 2
		&& !ft_check_lastchar(input_string, '\''))
		return (22);
	else if (ft_check_totalchar(input_string, '\'') >= 2)
		return (26);
	else if (!ft_strncmp(input_string, "\'", 1)
		&& ft_check_lastchar(input_string, '\''))
		return (24);
	else if (ft_check_totalchar(input_string, '\'') == 1)
		return (28);
	else if (ft_creat_dquoted_token(input_string))
		return (ft_creat_dquoted_token(input_string));
	else
		return (20);
}
