/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_op_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:24:46 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/19 15:04:01 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION:
 * in this file there are listed 2 functions that search for 
 * different kinds of operators, required for lexer-part of minishell,
 * to clean the command line input string
 */
/**
 * @brief function that checks for double operators
 *
 * @param c the first char to search in
 * @param k the second char to search in
 */
bool	double_operator_check(char c, char k)
{
	if ((c == '<' && k == '<') || (c == '>' && k == '>'))
		return (1);
	else
		return (0);
}

/**
 * @brief function that checks for single operators
 *
 * the functionality of ";" is not implemented
 * || (c == ';')
 * 
 * @param c the char to search in
 */
bool	single_operator_check(char c)
{
	if ((c == '<') || (c == '>') || (c == '|'))
		return (1);
	else
		return (0);
}
