
#include "minishell.h"
// to be able to use tgetstr
// #include <curses.h>
// #include <term.h>

/**
 * DESRIPTION: 
 * in this file the cleaned input and by delimiters separated array of strings
 * (1) will be transformed to a linked list called lexx
 * (2) data of linked list will be initiated (esps. the tokens)
 * (?3?) analyses data if command line input has to be expanded 
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
 * @brief function to check the occurance of char in string
 * 
 * @param content the string to search in
 * @param checker the char to search for
 */
static int	ft_check_totalchar(char *content, char checker)
{
	int	i;

	i = 0;
	while (*content)
	{
		if (*content == checker)
			i++;
		content++;
	}
	return (i);
}

/**
 * @brief helper function for ft_creat_str_token, 
 * that checks if last character of string content
 * is equal to char checker
 * 
 * @param content the string to seach in
 * @param checker the char to search for
 */
static bool	ft_check_lastchar(char *content, char checker)
{
	if (content[ft_strlen(content) - 1] == checker)
		return (0);
	else
		return (1);
}

/**
 * @brief helper function of ft_creat_tokens
 * to initiate variable token of linked list lexx,
 * here: alls kinds of strings
 * 
 * @param input_arr string with cleaned input of 
 * command line input
 */
static t_tokentype	ft_creat_str_token(char *input_arr)
{
	if (!ft_strncmp(input_arr, "\'", 1)
		&& !ft_check_lastchar(input_arr, '\''))
		return (22);
	else if (!ft_strncmp(input_arr, "\'", 1)
		&& ft_check_lastchar(input_arr, '\'')
		&& ft_check_totalchar(input_arr, '\'') > 1)
		return (25);
	else if (!ft_strncmp(input_arr, "\'", 1)
		&& ft_check_lastchar(input_arr, '\''))
		return (24);
	else if (!ft_strncmp(input_arr, "\"", 1)
		&& !ft_check_lastchar(input_arr, '\"'))
		return (21);
	else if (!ft_strncmp(input_arr, "\"", 1)
		&& ft_check_lastchar(input_arr, '\"')
		&& ft_check_totalchar(input_arr, '\"') > 1)
		return (25);
	else if (!ft_strncmp(input_arr, "\"", 1)
		&& ft_check_lastchar(input_arr, '\"'))
		return (23);
	else
		return (20);
}

/**
 * @brief helper function of ft_creat_tokens
 * to initiate variable token of linked list lexx,
 * here: alls kinds of redirections
 * 
 * @param input_arr string with cleaned input of 
 * command line input
 */
static t_tokentype	ft_creat_redir_token(char *input_arr)
{
	if ((!ft_strncmp(input_arr, ">>", ft_strlen(">>")) 
			&& ft_strlen(input_arr) == ft_strlen(">>")))
		return (6);
	else if ((!ft_strncmp(input_arr, ">", ft_strlen(">")) 
			&& ft_strlen(input_arr) == ft_strlen(">")))
		return (5);
	else if ((!ft_strncmp(input_arr, "<<", ft_strlen("<<")) 
			&& ft_strlen(input_arr) == ft_strlen("<<")))
		return (3);
	else if ((!ft_strncmp(input_arr, "<", ft_strlen("<")) 
			&& ft_strlen(input_arr) == ft_strlen("<")))
		return (4);
	else 
		return (0);
}

/**
 * @brief function to initiate variable token of linked list lexx,
 * here: operators (except redirect operators)
 * 
 * @param input_arr string with cleaned input of 
 * command line input
 */
static t_tokentype	ft_creat_tokens(char *input_arr)
{
	t_tokentype	token;

	token = 0;
	if ((!ft_strncmp(input_arr, "|", ft_strlen("|")) 
			&& ft_strlen(input_arr) == ft_strlen("|")))
		token = 1;
	else if ((!ft_strncmp(input_arr, ";", ft_strlen(";")) 
			&& ft_strlen(input_arr) == ft_strlen(";")))
		token = 2;
	else
	{
		token = ft_creat_redir_token(input_arr);
		if (!token)
			token = ft_creat_str_token(input_arr);
	}
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
