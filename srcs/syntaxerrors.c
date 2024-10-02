
#include "minishell.h"

/**
 * DESRIPTION: 
 * this file organises the error handling of 
 * syntax errors of command line input
 */

void	ft_syntax_errors(t_list *lexx, int errorno)
{
	if (errorno == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(((t_lexer *)lexx->content)->value, 2);
		ft_putstr_fd("\'\n", 2);
		// ft_printf("minishell: syntax error near unexpected "
			// "token \'%s\'\n", ((t_lexer *)lexx->content)->value);
	}
	else if (errorno == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline\'\n", 2);
		// ft_printf("minishell: syntax error near "
			// "unexpected token \'newline\'\n", ((t_lexer *)lexx->content)->value);
	}
	else if (errorno == 3)
	{
		ft_putstr_fd("minishell: unclosed quotes cannot be interpreted in this version: `", 2);
		ft_putstr_fd(((t_lexer *)lexx->content)->value, 2);
		ft_putstr_fd("\'\n", 2);
		// ft_printf("minishell: unclosed quotes cannot be interpreted "
		// 	"in this version: \'%s\'\n", ((t_lexer *)lexx->content)->value);
	}
	else if (errorno == 4)
	{
		ft_putstr_fd("minishell: command line input contains bonus part operators: `", 2);
		ft_putstr_fd(((t_lexer *)lexx->content)->value, 2);
		ft_putstr_fd("\'\n", 2);
		// ft_printf("minishell: command line input contains bonus part operators:"
		// 	" \'%s\'\n", ((t_lexer *)lexx->content)->value);
	}
}
