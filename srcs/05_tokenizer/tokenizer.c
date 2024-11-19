/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:21:49 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 12:21:53 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the cleaned input and by delimiters separated array of strings
 * (1) will be transformed to a linked list called lexx and
 * (2) tokens will be will be added to each node
 */

/**
 * @brief function to initiate variable token of linked list lexx
 * (devided into operator tokens, redirection tokens, string tokens)
 * if the token 25 or 26 was set, special treatment has to be implemented
 * to check this input tokens for unclosed quotes
 * 
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 */
static t_tokentype	ft_creat_tokens(char *input_string)
{
	t_tokentype	token;

	token = 0;
	if (ft_creat_operators_token(input_string))
		token = ft_creat_operators_token(input_string);
	else if (ft_creat_redir_token(input_string))
		token = ft_creat_redir_token(input_string);
	else
		token = ft_creat_str_token(input_string);
	if (token == 25 || token == 26)
		ft_qword_quotecheck(input_string, &token);
	return (token);
}

/**
 * @brief this function transforms the array of strings to linked list
 * by copying the string to value and adding a specific token to the list
 * in case of token 3 (redirect in heredoc), it assigns as 
 * specific token value (= 30) to the node that comes after (=limiter),
 * as this node has to be excluded from expander
 * 
 * @param input_arr the cleaned array of strings created out of the 
 * command line input
 * @param lexx linked list to prepare all important variables for
 * syntax analysis
 */
static void	ft_init_llist(char **input_arr, t_list **lexx)
{
	t_lexer	*lexx_input;

	lexx_input = NULL;
	while (*input_arr)
	{
		lexx_input = ft_calloc(1, sizeof(t_lexer));
		lexx_input->value = ft_strdup(*input_arr);
		lexx_input->token = ft_creat_tokens(*input_arr);
		ft_lstadd_back(lexx, ft_lstnew(lexx_input));
		if (lexx_input->token == 3)
		{
			input_arr += 1;
			if (*input_arr)
			{
				lexx_input = ft_calloc(1, sizeof(t_lexer));
				lexx_input->value = ft_strdup(*input_arr);
				lexx_input->token = ft_creat_tokens(*input_arr);
				if (lexx_input->token == 20)
					lexx_input->token = 30;
				ft_lstadd_back(lexx, ft_lstnew(lexx_input));
			}
		}
		if (*input_arr)
			input_arr += 1;
	}
}

/**
 * this function creates a linked list
 * and sends this to a function which initiates this list
 * 
 * @param input_arr the cleaned array of strings created out of the 
 * command line input
 */
t_list	*ft_tokenizer(char **input_arr)
{
	t_list	*lexx;

	lexx = NULL;
	ft_init_llist(input_arr, &lexx);
	return (lexx);
}
