
#include "minishell.h"

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
 * test function to print the content of the linked list
 */
static void	test_print(t_list *lexx)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = lexx->next;
	while (lexx->next != NULL)
	{
		ft_printf("node (%i): %s", i, lexx->value);
		i++;
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
		ft_lstadd_back(lexx, ft_lstnew(*input_arr));
		input_arr++;
	}

}

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
	test_print(lexx);
	if (((ft_lstlast(lexx))->token == 'DOUBLE-QUOTED'
			&& (ft_lstlast(lexx))->content[(ft_strlen(content) - 1)] != "\"")
		|| ((ft_lstlast(lexx))->token == 'SINGLE-QUOTED'
			&& (ft_lstlast(lexx))->content[(ft_strlen(content) - 1)] != "\'"))
			ft_expander(&lexx);
}


