
#include "minishell.h"

/**
 * DESRIPTION: 
 * this file organises the error handling of 
 * syntax errors of command line input
 */

void	ft_syntax_errors(t_list *lexx, int errorno)
{
	if (errorno == 1)
		ft_printf("minishell: syntax error near unexpected "
			"token \'%s\'\n", ((t_lexer *)lexx->content)->value);
	else if (errorno == 2)
		ft_printf("minishell: syntax error near "
			"unexpected token \'newline\'\n", ((t_lexer *)lexx->content)->value);
	else if (errorno == 3)
		ft_printf("minishell: unclosed quotes cannot be interpreted "
			"in this version: \'%s\'\n", ((t_lexer *)lexx->content)->value);
}
