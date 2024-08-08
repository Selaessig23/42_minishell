
#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the lexer linked list will be used for 
 * checking grammar and syntax errors of command line input
 */

/**
 * @brief function that checks if there are words before 
 * and after a redirect signal
 * 
 * @param lexx linked list with cleaned command line input
 */
static int	ft_redirect_check(t_list *lexx)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if ((((t_lexer *)curr->content)->token >= 3 
				&& ((t_lexer *)curr->content)->token <= 6)
			&& (((t_lexer *)curr->next->content)->token < 20))
		{
			ft_syntax_errors(lexx->next, 1);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

/**
 * @brief function that checks if there are words before an after pipe
 * 
 * @param lexx linked list with cleaned command line input
 */
/*
static int	ft_pipe_check(t_list *lexx)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if (curr->next != NULL
			&& curr->next->token == 4
			&& curr->next->next != NULL
			&& ((curr->token > 3
					&& curr->token != 10)
				|| (curr->next->next->token > 3
					&& curr->next->next->token != 10)))
		{
			ft_syntax_errors(lexx, 1);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}
*/

/**
 * @brief function that checks very first input argument
 * 
 * @param start first node of cleaned command line input
 */
static int	ft_start_check(t_list *start)
{
	if (((t_lexer *)start->content)->token == 1)
	{
		ft_syntax_errors(start, 1);
		return (1);
	}
	else if ((((t_lexer *)start->content)->token <= 6 
			&& ((t_lexer *)start->content)->token >= 3)
		&& start->next == NULL)
	{
		ft_syntax_errors(start, 2);
		return (1);
	}
	return (0);
}

/**
 * @brief function that checks for unclosed quotes,
 * command line inputs with unclosed input cannot be 
 * interpreted in our first version
 * 
 * @param lexx linked list with cleaned command line input
 */
static int	ft_quotes_check(t_list *lexx)
{
	t_list	*curr;

	curr = lexx;
	// ft_printf("test token: %d\n", (int)curr->token);
	while (curr != NULL)
	{
		if (((t_lexer *)curr->content)->token == 23
			|| ((t_lexer *)curr->content)->token == 24)
		{
			ft_syntax_errors(curr, 3);
			return (1);
		}
		curr = curr->next;
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
	if (ft_quotes_check(lexx))
		return (1);
	else if (ft_start_check(lexx))
		return (1);
	else if (ft_redirect_check(lexx))
		return (1);
	// else if (ft_pipe_check(lexx))
	// 	return (1);
	return (0);
}