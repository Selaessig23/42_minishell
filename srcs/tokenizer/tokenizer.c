
#include "minishell.h"
// to be able to use tgetstr
// #include <curses.h>
// #include <term.h>

/**
 * DESRIPTION: 
 * in this file the cleaned input and by delimiters separated array of strings
 * (1) will be transformed to a linked list called lexx
 * (2) data of linked list will be initiated (esps. the tokens)
 */

/**
 * @helper function for ft_qword_special which returns the pointer 
 * to part of string after second "\'" if token == 26 or
 * pointer to part of string after second "\"" if token == 25 or 
 * pointer to part of string after second quote (depends 
 * on which kind of quote comes first in string) if there is no exact
 * information about the token (=0) 
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 * @param token
 * @param returner a bool variable which sets input_string to its original value
 * if value is set on true
 */
char	*ft_get_quotendpointer(char *input_string, t_tokentype token, bool returner)
{
	int		i;
	char	countsign;
	char	*input_string_copy;

	i = 0;
	input_string_copy = input_string;
	if (token == 25)
		countsign = '\"';
	else if (token == 26)
		countsign = '\'';
	else if (!ft_check_fstquote(input_string, '\"'))
		countsign = '\"';
	else
		countsign = '\'';
	while (*input_string && i <= 1)
	{
		if (*input_string == countsign)
			i += 1;
		input_string += 1;
	}
	if (i <= 1)
	{
		printf("run quotepointer: %s\n", input_string);
		if (returner == true)
			input_string = input_string_copy;
		return (NULL);
	}
	else
	{
		printf("run quotepointer: %s\n", input_string);
		return (input_string);
	}
}

/**
 * @brief function to handle a special case
 * of command line input in token 
 * D_Q_WORD = 25, e. g. "argument1"withoutspaceafter"quotes''""
 * S_Q_WORD = 26, // e. g. argument1'withoutspace'afterquotes'"'"...
 * if any of this tokens end up with an unequal number of quotes
 * (whether single or double) they have to be handled as 
 * cases with unclosed qoutation marks
 * 
 * function ft_creat_str_token in tokenizer_strings.c
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 * @param token_old the token that has to be checked for
 */
void	ft_qword_special(char *input_string, t_tokentype *token_old)
{
	// t_tokentype	token_new;
	int		count_squote;
	int		count_dquote;
	char	*input_string_copy;

	count_squote = 0;
	count_dquote = 0;
	input_string_copy = input_string;
	//test
	while (*input_string_copy && (ft_get_quotendpointer(input_string_copy, 0, true) != NULL))
		input_string_copy = ft_get_quotendpointer(input_string_copy, 0, 0);
	//testend
	printf("quotepointer final: %s\n", input_string_copy);
	while (*input_string_copy)
	{
		if (*input_string_copy == '\'')
			count_squote += 1; 
		else if (*input_string_copy == '\"')
			count_dquote += 1;
		input_string_copy += 1;
	}
	printf("test count_squote: %i\ntest count_dquote: %i\n", count_squote, count_dquote);
	if (count_squote != 0 && (count_squote % 2 != 0) && (!ft_check_fstquote(input_string_copy, '\''))
		//get pointer to part of string after second "\'" if token == 26 or
		//get pointer to part of string after second "\"" if token == 25
		// && !ft_check_fstquote(ft_get_quotendpointer(input_string_copy, *token_old), '\'')
	)
		*token_old = 28;
	else if (count_dquote != 0 && (count_dquote % 2 != 0)
		//get pointer to part of string after second "\'" if token == 26 or
		//get pointer to part of string after second "\"" if token == 25
		// && !ft_check_fstquote(pointer, '\"')
		// && !ft_check_fstquote(ft_get_quotendpointer(input_string_copy, *token_old), '\"')
	)
	{
		*token_old = 27;
		printf("test2\n");
	}	
	// else
	// 	token_new = *token_old;
	// token_old = &token_new;
}

/**
 * @brief function to initiate variable token of linked list lexx
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 */
static t_tokentype	ft_creat_tokens(char *input_string)
{
	t_tokentype	token;

	token = 0;
	if (ft_creat_operators_token(input_string))
		token = ft_creat_operators_token(input_string);
	// if ((!ft_strncmp(input_string, "|", ft_strlen("|")) 
	// 		&& ft_strlen(input_string) == ft_strlen("|")))
	// 	token = 1;
	// else if ((!ft_strncmp(input_string, ";", ft_strlen(";")) 
	// 		&& ft_strlen(input_string) == ft_strlen(";")))
	// 	token = 2;
	else if (ft_creat_redir_token(input_string))
		token = ft_creat_redir_token(input_string);
	else
		token = ft_creat_str_token(input_string);
	printf("token_defined: %i\n", token);
	if (token == 25 || token == 26)
		ft_qword_special(input_string, &token);
	return (token);
}

/**
 * @brief this function transforms the array of strings to linked list
 * 
 * @param input_arr the cleaned array of strings created out of the 
 * command line input
 * @param lexx linked list to prepare all important variables for
 * syntax analysis
 */
static void	ft_init_llist(char **input_arr, t_list **lexx)
{
	t_lexer	*lexx_input;

	lexx_input = NULL;
	while (*input_arr)
	{
		lexx_input = ft_calloc(1, sizeof(t_lexer));
		lexx_input->value = ft_strdup(*input_arr);
		lexx_input->token = ft_creat_tokens(*input_arr);
		ft_lstadd_back(lexx, ft_lstnew(lexx_input));
		input_arr++;
	}
}

/**
 * @brief function that checks if the command line input requires
 * a new line
 * 
 * @param
 */
// static void	ft_cline_expander(t_list *lexx)
// {
// 	t_list	*curr;
// 	int	check;
// 	const char	*id;
// 	char	**area;

// 	curr = lexx;
// 	check = 0;
// 	id = NULL;
// 	area = NULL;
// 	while (curr != NULL)
// 	{
// 		check = 0;
// 		if (curr->token == 8
// 			|| curr->token == 9)
// 		{
// 			tgetstr(id, area);
// 		}
// 		if (check > 0)
// 		{
// 			while (**area)
// 			{
// 				ft_printf("test getstr: %s", **area);
// 				area++;
// 			}
// 		}
// 		curr = curr->next;
// 	}
// }

/**
 * this function organises the tokenizing of the cleaned input array
 * 
 * @param input_arr the cleaned array of strings created out of the 
 * command line input
 */
t_list	*ft_tokenizer(char **input_arr)
{
	t_list	*lexx;

	lexx = NULL;
	ft_init_llist(input_arr, &lexx);
	return (lexx);
}
