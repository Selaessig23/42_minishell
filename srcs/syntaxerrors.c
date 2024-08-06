
#include "minishell.h"

/**
 * DESRIPTION: 
 * this file organises the error handling of 
 * syntax errors of command line input
 */

void	ft_syntax_errors(t_list *lexx, int errorno)
{
	if (errorno == 1)
		ft_printf("minishell: syntax error near unexpected token \'%s\'\n", lexx->content);
	else if (errorno == 2)
		ft_printf("minishell: syntax error near unexpected token \'newline\'\n", lexx->content);
}
