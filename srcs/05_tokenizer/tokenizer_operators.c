/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_operators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:32:53 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/18 09:11:49 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the cleaned input and by delimiters separated array of strings
 * will be checked for all kinds of operator definitions (tokens < 20). 
 * On basis of that, specific tokens will be added. 
 */

/**
 * @brief helper function of ft_creat_tokens
 * to initiate variable token of linked list lexx,
 * here: alls kinds of redirections
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 */
t_tokentype	ft_creat_redir_token(char *input_string)
{
	if ((!ft_strncmp(input_string, ">>", ft_strlen(">>")) 
			&& ft_strlen(input_string) == ft_strlen(">>")))
		return (6);
	else if ((!ft_strncmp(input_string, ">", ft_strlen(">")) 
			&& ft_strlen(input_string) == ft_strlen(">")))
		return (5);
	else if ((!ft_strncmp(input_string, "<<", ft_strlen("<<")) 
			&& ft_strlen(input_string) == ft_strlen("<<")))
		return (3);
	else if ((!ft_strncmp(input_string, "<", ft_strlen("<")) 
			&& ft_strlen(input_string) == ft_strlen("<")))
		return (4);
	else 
		return (0);
}

/**
 * @brief helper function of ft_creat_tokens
 * to initiate variable token of linked list lexx,
 * here: operators (except redirect operators)
 * 
 * 	// else if ((!ft_strncmp(input_string, ";", ft_strlen(";")) 
	// 		&& ft_strlen(input_string) == ft_strlen(";")))
	// 	return (2);
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 */
t_tokentype	ft_creat_operators_token(char *input_string)
{
	if ((!ft_strncmp(input_string, "|", ft_strlen("|")) 
			&& ft_strlen(input_string) == ft_strlen("|")))
		return (1);
	else
		return (0);
}
