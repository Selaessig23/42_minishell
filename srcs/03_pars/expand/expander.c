/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:48:05 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 13:48:12 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the cleaning (deletion) and extension of parts of 
 * specific tokens of type strings (>= 20) is organised
 */

/**
 * @brief function that checks if there is a $-sign within the 
 * specific string sent by ft_expa_precond and send the string 
 * to further functions according to the special parameter
 * 
 * $$, $#, $*, $@, $0, $1.., $[10].., $_, $!, $-, $, $$ are not
 * treated and therefor not seen as special character
 * except $env and $?
 * 
 * it would have been nicer to dereference node_content by using an
 * additional variable, like
 * t_lexer	*temp;
 * temp = *node_content;
 * value_old = temp->value;
 * temp->value = value_new;
 * But there are not enough lines left according to norminette
 * 
 * @param node_content node of token-list that has to be cleaned from quotes
 * @param big structure which contains the environmental variable array
 */
void	ft_var_checker(void	**node_content, t_big *big)
{
	char	*value_new;
	char	*value_old;
	int		i;

	i = 0;
	value_new = NULL;
	value_old = ((t_lexer *)(*node_content))->value;
	while (value_old[i])
	{
		if (value_old[i + 1] && value_old[i] == '$'
			&& !((value_old[i + 1] == '$') || (value_old[i + 1] == ' ')))
		{
			if (value_old[i + 1] == '?')
				value_new = ft_exit_expander(value_old, big->exit_code);
			else
				value_new = ft_var_creator(value_old, big->env);
			((t_lexer *)(*node_content))->value = value_new;
			free (value_old);
			value_old = NULL;
			value_old = ((t_lexer *)(*node_content))->value;
		}
		if (value_old[i])
			i += 1;
	}
}

/**
 * @brief function that organises the expansion and reduction
 * of command line input by checking for specific string tokens
 * 
 * MISSING, if shell should handle UNCLOSED QUOTES: delete them
 * 
 * @param lexx linked list with cleaned command line input and tokens
 * @param big structure which contains the environmental variable array
 */
void	ft_expa_precond(t_list *lexx, t_big *big)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if ((((t_lexer *)curr->content)->token == 21)
			|| (((t_lexer *)curr->content)->token == 22))
			ft_quote_checker(&curr->content);
		else if ((((t_lexer *)curr->content)->token == 25)
			|| (((t_lexer *)curr->content)->token == 26))
			ft_q_word_handling(&curr->content, big);
		if ((((t_lexer *)curr->content)->token == 20)
			|| (((t_lexer *)curr->content)->token == 21)
			|| (((t_lexer *)curr->content)->token == 25))
			ft_var_checker(&curr->content, big);
		curr = curr->next;
	}
}
