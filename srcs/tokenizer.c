
#include "minishell.h"
// #include <curses.h>
// #include <term.h>

/**
 * DESRIPTION: 
 * in this file the cleaned input and by delimiters separated array of strings
 * (1) will be transformed to a linked list called lexer
 * (2) data of linked list will be initiated (esps. the tokens)
 * (3) analyses data if command line input has to be expanded
 * if last token of linked list is quoted string && last char of value does  
 * 3rd / 4th (?) it integrates variables if listed within a word 
 * and deletes the quotesexer-part of creati
 * 3rd / 4th it creates an linked list out of the array of strings 
 * wich saves command right, command left, value, token (word / operator)
 */

/**
 * function to free the linked list
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
		free(temp);
	}
	curr = NULL;
}
bool helper(char *content, char checker)
{
	if (content[ft_strlen(content) - 1] == checker)
		return (0);
	else
		return (1);
}
/**
 * 
 */
static void	ft_creat_str_token(t_list *lexx)
{
	if (!ft_strncmp(lexx->content, "\'", 1)
		&& !helper(lexx->content, '\''))
		lexx->token = 2;
	else if (!ft_strncmp(lexx->content, "\'", 1)
		&& helper(lexx->content, '\''))
		lexx->token = 9;
	else if (!ft_strncmp(lexx->content, "\"", 1)
		&& !helper(lexx->content, '\"'))
		lexx->token = 3;
	else if (!ft_strncmp(lexx->content, "\"", 1)
		&& helper(lexx->content, '\"'))
		lexx->token = 8;
	else
		lexx->token = 1;

}

/**
 * @brief function to initiate the tokens
 * 
 * @param lexx linked list with cleaned input of 
 * command line input
 */
static void	ft_creat_tokens(t_list *lexx)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if ((!ft_strncmp(curr->content, "|", ft_strlen("|")) 
				&& ft_strlen(curr->content) == ft_strlen("|")))
			curr->token = 4;
		else if ((!ft_strncmp(curr->content, ">>", ft_strlen(">>")) 
				&& ft_strlen(curr->content) == ft_strlen(">>")))
			curr->token = 5;
		else if ((!ft_strncmp(curr->content, ">", ft_strlen(">")) 
				&& ft_strlen(curr->content) == ft_strlen(">")))
			curr->token = 6;
		else if ((!ft_strncmp(curr->content, "<", ft_strlen("<")) 
				&& ft_strlen(curr->content) == ft_strlen("<")))
			curr->token = 7;
		else
			ft_creat_str_token(curr);
		curr = curr->next;
	}
}

/**
 * @brief this function transforms the array of strings to linked list
 * 
 * @param input_arr the cleaned array of strings created out of the 
 * command line input
 */
static void	ft_creat_list(char **input_arr, t_list **lexx)
{
	while (*input_arr)
	{
		// ft_printf("test: %s\n", *input_arr);
		ft_lstadd_back(lexx, ft_lstnew(*input_arr));
		// ft_printf("test 2\n");
		input_arr++;
		// ft_printf("test: %s\n", *input_arr);
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
	ft_creat_list(input_arr, &lexx);
	ft_creat_tokens(lexx);
	// ft_cline_expander(lexx);
	// if (((ft_lstlast(lexx))->token == 'DOUBLE-QUOTED'
	// 		&& (ft_lstlast(lexx))->content[(ft_strlen(content) - 1)] != "\"")
	// 	|| ((ft_lstlast(lexx))->token == 'SINGLE-QUOTED'
	// 		&& (ft_lstlast(lexx))->content[(ft_strlen(content) - 1)] != "\'"))
	// 		ft_expander(&lexx);
	return (lexx);
}
