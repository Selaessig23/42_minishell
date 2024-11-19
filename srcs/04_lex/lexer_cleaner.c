/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:39:59 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/18 15:03:12 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION:
 * in this file the input cleaning is organised by writing 
 * to a new cleaned_input-string adding spaces before and after 
 * single-char-operators and double-char-operators
 * (if not within quotes)
 */
/**
 * @brief a helper function for ft_create_clean_input
 * it loops through not necessary parts of a string
 * (within quotes)
 * while continuing copying from src
 * if (src[i] == '\"') || if (src[i] == '\'')
 * 
 * AVOID USING "++" !!!
 *
 * @param dest the destination pointer to copy in
 * @param src the source pointer to copy from
 * @param endsign the sign until the indexer should copy to
 */
static void	ft_jump_copy(char **dest, char **src, char endsign)
{
	**dest = **src;
	if (*(*src + 1) == endsign)
	{
		(*dest)++;
		(*src)++;
		**dest = **src;
	}
	else if (*(*src + 1) != '\0')
	{
		(*dest)++;
		(*src)++;
		*(*dest)++ = *(*src)++;
		while (*(*src) && *(*src) != endsign)
			*(*dest)++ = *(*src)++;
		if (*(*src) != '\0')
			**dest = **src;
	}
}

/**
 * @brief a helper function for ft_create_clean_input;
 * it adds spaces before and after operators
 *
 * @param dest the destination string where to integrate additional
 * spaces before an after operators
 * @param src the source string required to create dest
 */
static void	ft_op_separator(char **dest, char **src)
{
	if (double_operator_check(*(*src), *(*src + 1)))
	{
		**dest = ' ';
		(*dest)++;
		**dest = **src;
		(*src)++;
		(*dest)++;
		**dest = **src;
		(*dest)++;
		**dest = ' ';
	}
	else
	{
		**dest = ' ';
		(*dest)++;
		**dest = **src;
		(*dest)++;
		**dest = ' ';
	}
}

/**
 * @brief this function checks for quotation marks and certain operators, 
 * manipulates the command line input under certain circumstances 
 * (= operator was found --> add spaces to dest)
 * and otherwise copies from src to dest directly
 * (unquoted operators have to be seperated by spaces)
 *
 * @param dest the destination string where to copy to
 * @param src the source string where to copy from
 */
void	ft_create_clean_input(char *dest, char *src)
{
	while (*src)
	{
		if (*src == '\"')
			ft_jump_copy(&dest, &src, '\"');
		else if (*src == '\'')
			ft_jump_copy(&dest, &src, '\'');
		else if (*(src) && 
			*(src + 1) && double_operator_check(*src, *(src + 1)))
			ft_op_separator(&dest, &src);
		else if (*(src) && single_operator_check(*src))
			ft_op_separator(&dest, &src);
		else if (*(src))
			*dest = *src;
		if (*src != '\0')
		{
			dest += 1;
			src += 1;
		}
	}
	*dest = '\0';
}
