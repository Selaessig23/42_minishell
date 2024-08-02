
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

/**
 * test function to print the content of the linked list
 */
static void	test_print(t_list *lexx)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = lexx;
	while (curr != NULL)
	{
		if (!ft_strncmp(curr->content, "exit", 4) 
			&& ft_strlen(curr->content) == 4)
		{
			//valgrind-error as prompt, input_arr, 
			ft_free_ll(&lexx);
			rl_clear_history();
			exit(EXIT_SUCCESS);
		}
		else if (!ft_strncmp(curr->content, "env", 3) 
			&& ft_strlen(curr->content) == 3)
		{
			while (*__environ)
			{
				ft_printf("%s\n", *__environ);
				__environ++;
			}
		}
		else
		{
			ft_printf("node (%i): %s\n", i, curr->content);
			if (!ft_strncmp(curr->content, "$USER", ft_strlen("$USER"))
				&& ft_strlen("$USER") == ft_strlen(curr->content))
				ft_printf("after expand function $USER is \"user_name\"\n");
		}
		i++;
		curr = curr->next;
	}
}

/**
 * @brief function to initiate the tokens
 * 
 * @param lexx linked list with cleaned input of 
 * command line input
 */
static void	ft_creat_tokens(&lex)
{
	t_list	*curr;
	
	curr = lexx;
	while (curr != NULL)
	{
		if ((!ft_strncmp(curr->content, ">", ft_strlen(">")) 
				&& ft_strlen(curr->content) == ft_strlen(">")))
			curr->token = REDIRECT_INPUT;
		else if ((!ft_strncmp(curr->content, "<", ft_strlen("<")) 
				&& ft_strlen(curr->content) == ft_strlen("<")))
			curr->token = REDIRECT_OUTPUT;
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
	ft_creat_tokens(&lex);
	// if (((ft_lstlast(lexx))->token == 'DOUBLE-QUOTED'
	// 		&& (ft_lstlast(lexx))->content[(ft_strlen(content) - 1)] != "\"")
	// 	|| ((ft_lstlast(lexx))->token == 'SINGLE-QUOTED'
	// 		&& (ft_lstlast(lexx))->content[(ft_strlen(content) - 1)] != "\'"))
	// 		ft_expander(&lexx);
	return (lexx);
}


