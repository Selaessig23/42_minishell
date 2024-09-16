
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
 * @brief function to free the linked list
 * 
 * @param ll the linked list to free
 */
void	ft_free_ll(t_list **ll)
{
	t_list	*temp;
	t_list	*curr;

	curr = *ll;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(((t_lexer *)temp->content)->value);
		free(temp->content);
		free(temp);
	}
	curr = NULL;
}

/**
 * @brief function to handle a special case
 * of command line input in token 
 * D_Q_WORD = 25, e. g. "argument1"withoutspaceafter"quotes''""
 * S_Q_WORD = 26, // e. g. argument1'withoutspace'afterquotes'"'"...
 */
void	ft_qword_special(t_tokentype *token_old)
{
	t_tokentype	token_new;

	(void) token_old;
	(void) token_new;
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
	if (token == 25 || token == 26)
		ft_qword_special(&token);
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
