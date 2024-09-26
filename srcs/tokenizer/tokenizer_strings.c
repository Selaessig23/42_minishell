#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the cleaned input and by delimiters separated array of strings
 * will be checked for all kinds of string defintions (tokens => 20). 
 * On basis of that, specific tokens will be added.
 */

/**
 * @brief function to check the occurance of char checker in string
 * 
 * @param content the string to search in
 * @param checker the char to search for
 * 
 * @return returns 0 if checker char is not 1st quotation found
 */
static int	ft_check_totalchar(char *content, char checker)
{
	int		i;

	i = 0;
	if (ft_check_fstquote(content, checker))
		return (-1);
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
 * @brief function to check for double qoutes and assign
 * a specific value (token) in case of
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input 
 */
static t_tokentype	ft_creat_dquoted_token(char *input_string)
{
	if (!ft_strncmp(input_string, "\"", 1)
		&& ft_check_totalchar(input_string, '\"') == 2
		&& !ft_check_lastchar(input_string, '\"'))
		return (21);
	// else if (ft_check_totalchar(input_string, '\"') >= 2
	// 	&& !(ft_check_totalchar(input_string, '\"') % 2))
	else if (ft_check_totalchar(input_string, '\"') >= 2)
		// && (ft_strncmp(input_string, "\"", 1) || ft_check_lastchar(input_string, '\"')))
		return (25);
	else if (!ft_strncmp(input_string, "\"", 1)
		&& ft_check_lastchar(input_string, '\"'))
		return (23);
	// else if (ft_check_totalchar(input_string, '\"') >= 0
		// && (ft_check_totalchar(input_string, '\"') % 2))
	else if (ft_check_totalchar(input_string, '\"') == 1)
		return (27);
	else 
		return (0);
}


/**
 * @brief helper function of ft_creat_tokens
 * to initiate variable token of linked list lexx,
 * here: alls kinds of strings with special focus on single quoted
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 */
t_tokentype	ft_creat_str_token(char *input_string)
{
	if (!ft_strncmp(input_string, "\'", 1)
		&& ft_check_totalchar(input_string, '\'') == 2
		&& !ft_check_lastchar(input_string, '\''))
		return (22);
	// else if (ft_check_totalchar(input_string, '\'') >= 2
		// && !(ft_check_totalchar(input_string, '\'') % 2))
	else if (ft_check_totalchar(input_string, '\'') >= 2)
		// && (ft_strncmp(input_string, "\'", 1) || ft_check_lastchar(input_string, '\'')))
		return (26);
	else if (!ft_strncmp(input_string, "\'", 1)
		&& ft_check_lastchar(input_string, '\''))
		return (24);
	// else if (ft_check_totalchar(input_string, '\'') >= 0
		// && (ft_check_totalchar(input_string, '\'') % 2) != 0)
	else if (ft_check_totalchar(input_string, '\'') == 1)
		return (28);
	else if (ft_creat_dquoted_token(input_string))
		return (ft_creat_dquoted_token(input_string));
	else
		return (20);
}
