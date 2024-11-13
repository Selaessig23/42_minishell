/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerrors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:12:29 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/13 14:12:32 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * this file organises the error message handling of 
 * syntax errors of command line input
 */

void	ft_syntax_errors(t_list *lexx, int errorno)
{
	if (errorno == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(((t_lexer *)lexx->content)->value, 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (errorno == 2)
	{
		ft_putstr_fd("minishell: syntax error near ", 2);
		ft_putstr_fd("unexpected token `newline\'\n", 2);
	}
	else if (errorno == 3)
	{
		ft_putstr_fd("minishell: unclosed quotes cannot be ", 2);
		ft_putstr_fd("interpreted in this shell: `", 2);
		ft_putstr_fd(((t_lexer *)lexx->content)->value, 2);
		ft_putstr_fd("\'\n", 2);
	}
	else if (errorno == 4)
	{
		ft_putstr_fd("minishell: command line input ", 2);
		ft_putstr_fd("contains bonus part operators: `", 2);
		ft_putstr_fd(((t_lexer *)lexx->content)->value, 2);
		ft_putstr_fd("\'\n", 2);
	}
}
