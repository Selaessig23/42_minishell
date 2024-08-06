
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
 * @brief function to initiate variable token of linked list lexx,
 * here: alls kinds of strings
 * 
 * @param linked list with cleaned input of 
 * command line input
 */
static void	ft_creat_str_token(t_list *lexx)
{
	if (!ft_strncmp(lexx->content, "\'", 1)
		&& !ft_check_lastchar(lexx->content, '\''))
		lexx->token = 3;
	else if (!ft_strncmp(lexx->content, "\'", 1)
		&& ft_check_lastchar(lexx->content, '\'')
		&& ft_check_totalchar(lexx->content, '\'') > 1)
		lexx->token = 10;
	else if (!ft_strncmp(lexx->content, "\'", 1)
		&& ft_check_lastchar(lexx->content, '\''))
		lexx->token = 9;
	else if (!ft_strncmp(lexx->content, "\"", 1)
		&& !ft_check_lastchar(lexx->content, '\"'))
		lexx->token = 2;
	else if (!ft_strncmp(lexx->content, "\"", 1)
		&& ft_check_lastchar(lexx->content, '\"')
		&& ft_check_totalchar(lexx->content, '\"') > 1)
		lexx->token = 10;
	else if (!ft_strncmp(lexx->content, "\"", 1)
		&& ft_check_lastchar(lexx->content, '\"'))
		lexx->token = 8;
	else
		lexx->token = 1;
}

/**
 * @brief function to initiate variable token of linked list lexx,
 * here: all operators
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
		ft_lstadd_back(lexx, ft_lstnew(ft_strdup(*input_arr)));
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
	return (lexx);
}
