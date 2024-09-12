#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the cleaned input and by delimiters separated array of strings
 * will be checked for all kinds of string defintions (tokens => 20)
 */

/**
 * @brief function to check which kind of quote comes first
 * function serves to avoid that quotations (e. g. ') 
 * within main quotations (e . g. "), are taken into account
 * 
 * @param content the string to search in
 * @param checker the char to search for
 * 
 * @return returns 0 if checker char is not 1st quotation found
 */
static int	ft_check_fstquote(char *content, char checker)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (checker == '\'')
		c = '\"';
	else if (checker == '\"')
		c = '\'';
	else
		c = '\0';
	while (content[i] && content[i] != c)
		i += 1;
	while (content[j] && content[j] != checker)
		j += 1;
	if ((i + j) == 0 || (i - j) == 0 || i < j)
		return (1);
	else
		return (0);
}

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
 * @brief helper function of ft_creat_tokens
 * to initiate variable token of linked list lexx,
 * here: alls kinds of strings
 * 
 * @param input_string string as part of input_arr with cleaned input of 
 * command line input
 */
t_tokentype	ft_creat_str_token(char *input_string)
{
	if (!ft_strncmp(input_string, "\'", 1)
		&& !ft_check_lastchar(input_string, '\''))
		return (22);
	else if (ft_check_totalchar(input_string, '\'') >= 2
		&& !(ft_check_totalchar(input_string, '\'') % 2))
		return (26);
	else if (ft_check_totalchar(input_string, '\'') >= 0
		&& (ft_check_totalchar(input_string, '\'') % 2) != 0)
		return (28);
	else if (!ft_strncmp(input_string, "\'", 1)
		&& ft_check_lastchar(input_string, '\''))
		return (24);
	else if (!ft_strncmp(input_string, "\"", 1)
		&& !ft_check_lastchar(input_string, '\"'))
		return (21);
	else if (ft_check_totalchar(input_string, '\"') >= 2
		&& !(ft_check_totalchar(input_string, '\"') % 2))
		return (25);
	else if (ft_check_totalchar(input_string, '\"') >= 0
		&& (ft_check_totalchar(input_string, '\"') % 2))
		return (27);
	else if (!ft_strncmp(input_string, "\"", 1)
		&& ft_check_lastchar(input_string, '\"'))
		return (23);
	else
		return (20);
}