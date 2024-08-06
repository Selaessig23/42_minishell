
#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the lexer linked list will be used for 
 * checking grammar and syntax errors of command line input
 */


/**
 * @brief function that checks very first input argument
 * 
 * @param lexx linked list with cleaned command line input
 */
static int	ft_start_check(t_list *start)
{
	if (start->token == 4)
	{
		ft_syntax_errors(start, 1);
		return (1);
	}
	else if ((start->token == 5 
			|| start->token == 6
			|| start->token == 7)
		&& start->next == NULL)
	{
		ft_syntax_errors(start, 2);
		return (2);
	}
	return (0);
}

/**
 * @brief function that organises the syntax analysis
 * 
 * @param lexx linked list with cleaned command line input
 */
int	ft_syntax(t_list *lexx)
{
	// t_list	*curr;

	if (ft_start_check(lexx))
		return (1);
	return (0);
}