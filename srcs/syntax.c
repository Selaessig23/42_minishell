#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the lexer linked list will be used for 
 * checking grammar and syntax errors of command line input
 */

/**
 * @brief function that checks if the command line input consists
 * of parts of the bonus part (use of || or &&)
 * 
 * @param lexx linked list with cleaned command line input
 */
static int	ft_bonus_check(t_list *lexx)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if (((t_lexer *)curr->content)->token == 11
			|| ((t_lexer *)curr->content)->token == 12)
		{
			ft_syntax_errors(lexx, 4);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

// /**
//  * @brief helper function for ft_pipe_check to search in 
//  * value of tokentype 21 (double quoted) for solid value "|"
//  * 
//  * @param token single node of the command line input
//  */
// static int	ft_pipe_special_check(t_lexer *token)
// {
// 	printf("token: %i, value: %s\n", token->token, token->value);
// 	if (token->token == 21 && ft_strncmp(token->value, "\"|\"", ft_strlen(token->value)))
// 		return (1);
// 	else
// 		return (0);

// }

/**
 * @brief function that checks if there is a further token pipe 
 * after token pipe
 * 
 * @param lexx linked list with cleaned command line input
 */
static int	ft_pipe_check(t_list *lexx)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if ((((t_lexer *)curr->content)->token == 1
				// || ((t_lexer *)curr->content)->token == 12
				)
			&& (curr->next != NULL
				&& ((((t_lexer *)curr->next->content)->token == 1)
					// || ft_pipe_special_check((t_lexer *)curr->next->content)
				// || ((t_lexer *)curr->next->content)->token == 12))
				)))
		{
			ft_syntax_errors(curr->next, 1);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

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
			&& (curr->next == NULL))

		{
			ft_syntax_errors(curr, 2);
			return (1);
		}
		else if ((((t_lexer *)curr->content)->token >= 3 
				&& ((t_lexer *)curr->content)->token <= 6)
			&& ((t_lexer *)curr->next->content)->token < 20)

		{
			ft_syntax_errors(curr->next, 1);
			return (1);
		}
		curr = curr->next;
	}
	// ft_printf("test3\n");
	return (0);
}

/**
 * @brief function that checks very first input argument
 * token 1 = |, 2 = ;
 * token 3 - 6 = redirect ops
 * 
 * @param start first node of cleaned command line input
 */
static int	ft_start_check(t_list *start)
{
	if (((t_lexer *)start->content)->token == 1
		|| ((t_lexer *)start->content)->token == 2)
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
	// ft_printf("test2\n");
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
			|| ((t_lexer *)curr->content)->token == 24
			|| ((t_lexer *)curr->content)->token == 27
			|| ((t_lexer *)curr->content)->token == 28)
		{
			ft_syntax_errors(curr, 3);
			return (1);
		}
		curr = curr->next;
	}
	// ft_printf("test1\n");
	return (0);
}

/**
 * @brief function that organises the syntax analysis
 * 
 * @param lexx linked list with cleaned command line input
 */
int	ft_syntax(t_list *lexx)
{
	// ft_printf("test0\n");
	if (ft_quotes_check(lexx))
	{
		// ft_printf("test quotes\n");
		return (1);
	}
	else if (ft_start_check(lexx))
	{
		// ft_printf("test start\n");
		return (1);
	}
	else if (ft_redirect_check(lexx))
	{
		// ft_printf("test redirect\n");
		return (1);
	}
	else if (ft_pipe_check(lexx))
	{	
		// ft_printf("test pipe\n");
		return (1);
	}
	else if (ft_bonus_check(lexx))
	{
		// ft_printf("test bonus\n");
		return (1);
	}
	return (0);
}
