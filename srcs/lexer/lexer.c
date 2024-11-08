#include "minishell.h"
/**
 * DESRIPTION:
 * in this file the lexer-part of creating the minishell is organised
 * 1st it searches for operators (except those in quotes)
 * and adds spaces before and after
 * 2nd it searches for spaces and tabs (except those in quotes)
 * and splits the input string from readline into an array of strings
 */

/**
 * @brief a helper function for ft_count,
 * it loops through not necessary parts of a string
 * (within quotes)
 * while continuing counting the indexer
 *
 * @param src the string to loop in
 * @param len the indexer to continue counting while iterating
 * @param endsign the sign until the indexer should jump to
 */
static char	*ft_jumper(char *src, int *len, char endsign)
{
	*len = *len + 1;
	src += 1;
	while (*src && *src != endsign)
	{
		(*len) += 1;
		src += 1;
	}
	return (src);
}

/**
 * @brief function that checks for occurence of unquoted operators
 * and calculates extra memory space (len) for adding spaces in
 * between
 *
 * @param src the string to count in
 */
static int	ft_count(char *src)
{
	int		len;
	char	*temp;

	len = 0;
	temp = src;
	while (*temp)
	{
		if (*temp == '\"')
			temp = ft_jumper(temp, &len, '\"');
		else if (*temp == '\'')
			temp = ft_jumper(temp, &len, '\'');
		if (*temp && *(temp + 1) && double_operator_check(*temp, *(temp + 1)))
		{
			len += 3;
			temp += 1;
		}
		else if (*temp && single_operator_check(*temp))
			len += 2;
		if (*temp)
		{
			len += 1;
			temp += 1;
		}
	}
	return (len);
}

/**
 * @brief function that creates a new cleaned input-string
 * with spaces for and after unquoted operators
 * trim_out_spaces deletes not required spaces (not very important
 * as spaces and tabs will be deleted by split function afterwards anyhow)
 * 
 * @param src the source string to clean
 * @return src in case there are no operators, otherwise dest_original
 */
static char	*ft_clean_input(char *src)
{
	char	*dest;
	size_t	len;

	dest = NULL;
	len = ft_count(src);
	if (len == (ft_strlen(src)))
		return (ft_strdup(src));
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
	{
		free(src);
		error_handling(2);
	}
	ft_create_clean_input(dest, src);
	trim_out_spaces(&dest);
	return (dest);
}

/**
 * @brief function that creates an array of strings and
 * organises the cleaning of command line 
 * (according to syntax rules) as well as checking 
 * for extra input in case of unclosed pipe
 * 
 * Marina:
 * - is_open_pipe - function that handles input with one | in the end.
 * - extra_prompt - function that takes additional input and concetanates it
 * - with readline_input.
 * Marina:
 * - changes in ft_clean_input: function that trim all leading 
 * and trailing spaces. 
 * (It might be that we don't need it, since later same job
 * will be done in ft_split_quotes)
 *
 * @param readline_input the input of command line read by function readline
 * @return: an array of strings with cleaned command line input
 */
char	**create_nodes(char **readline_input)
{
	char	*clean_input;
	char	**input_arr;
	// t_list	*lexx;

	// lexx = NULL;
	clean_input = NULL;
	input_arr = NULL;
	//// if (extra_prompt == NULL)
	//       return (NULL);
	while (is_open_pipe(*readline_input))
	{
		if (signalnum == 1)
		{
			input_arr = NULL;
			return (input_arr);
		}
		close_pipe(readline_input);
	}
	clean_input = ft_clean_input(*readline_input);
	if (!clean_input)
	{
		ft_free(readline_input);
		error_handling(2);
	}
	input_arr = ft_split_quotes(clean_input, ' ');
	free(clean_input);
	clean_input = NULL;
	if (!input_arr)
	{
		// TODO: error_handling;
		exit(EXIT_FAILURE);
	}
	// lexx = ft_tokenizer(input_arr);
	// return (lexx);
	return (input_arr);
}
