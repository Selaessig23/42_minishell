
#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the lexer-part of creating a shell (NAME?) is organised
 * 1st it searches for operators (except those in quotes) 
 * and adds spaces before and after
 * 2nd it searches for spaces (except those in quotes) 
 * and splits the input string from readline into an array of strings
 * 3rd / 4th (?) it integrates variables if listed within a word 
 * and deletes the quotes
 * 3rd / 4th it creates an linked list out of the array of strings 
 * wich saves command right, command left, value, token (word / operator)
 */


/**
 * @brief function that checks for double operators
 * 
 * @param c the first char to search in
 * @param k the second char to search in
 */
static bool	double_operator_check(char c, char k)
{
	if ((c == '<' && k == '<')
		|| (c == '>' && k == '>'))
		return (1);
	else
		return (0);
}

/**
 * @brief function that checks for single operators
 * 
 * @param c the char to search in
 */
static bool	single_operator_check(char c)
{
	if ((c == '<')
		|| (c == '>')
		|| (c == '|')
		|| (c == '$')
		|| (c == ';'))
		return (1);
	else
		return (0);
}

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
	len++;
	src++;
	while (*src && *src != endsign)
	{
		len++;
		src++;
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
	while (*src)
	{
		if (*src == '\"')
			temp = ft_jumper(src, &len, '\"');
		else if (*src == '\'')
			temp = ft_jumper(src, &len, '\'');
		if (double_operator_check(*src, *(src + 1)))
		{
			len += 3;
			src++;
		}
		else if (single_operator_check(*src))
			len += 2;
		if (*src)
		{
			len++;
			src++;
		}
	}
	return (len);
}

/**
 * @brief a helper function for ft_clean_input;
 * it adds spaces before and after operators
 * 
 * @param dest the destination string where to integrate additional 
 * spaces before an after operators
 * @param src the source string to create dest
 * @param i index of src
 * @param j index of dest
 */
static void	ft_op_separator(char *dest, char *src, int *i, int *j)
{
	(void) i;
	//double
	// if (double_operator_check(*src, *(src + 1)))
	// {
	// 	*dest = ' ';
	// 	dest++;
	// 	j++;
	// 	*dest = *src;
	// 	i++;
	// 	src++;
	// 	j++;
	// 	dest++;
	// 	*dest = *src;
	// 	dest++;
	// 	j++;
	// 	*dest = ' ';
	// }
	// //single
	// else
	// {
		*dest = ' ';
		dest++;
		*j = *j + 1;
		*dest = *src;
		dest++;
		*j = *j + 1;
		*dest = ' ';
	// }
}


/**
 * @brief function that creates a new cleaned input-string 
 * with spaces between operators if there are no in src
 * 
 * @param src the source string to clean
 * @return src in case there are no operators 
 * (MAYBE ADAPT ALSO TO THE CASE, IF THERE ARE NO "INCLUDED" OPERATORS), otherwise
 * a cleaned version of src (operators were liberated) is returned
 */
static char	*ft_clean_input(char *src)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;

	dest = NULL;
	len = ft_count(src);
	ft_printf("malloced len for cleaned input: %i\n", len);
	i = 0;
	j = 0; 
	if (len == (ft_strlen(src)))
	{
		ft_printf("No modification of input required. Delete this message\n");
		return (ft_strdup(src));
	}
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (src[i])
	{
		if (src[i] == '\"')
		{
			dest[j] = src[i];
			if (src[i + 1] == '\"')
			{
				j++;
				i++;
				dest[j] = src[i];
			}
			else if (src[i + 1] != '\0')
			{
				j++;
				i++;
				dest[j++] = src[i++];
				while (src[i] && src[i] != '\"')
					dest[j++] = src[i++];
				if (src[i] != '\0')
					dest[j] = src[i];
			}
		}
		else if (src[i] == '\'')
		{
			dest[j] = src[i];
			if (src[i + 1] == '\'')
			{
				j++;
				i++;
				dest[j] = src[i];
			}
			else if (src[i + 1] != '\0')
			{
				i++;
				j++;
				dest[j++] = src[i++];
				while (src[i] && src[i] != '\'')
					dest[j++] = src[i++];
				if (src[i] != '\0')
					dest[j] = src[i];
			}
		}
		else if (double_operator_check(src[i], src[i + 1]))
		{
			// ft_op_separator(&dest[j], &src[i], &i, &j);
			dest[j] = ' ';
			j++;
			dest[j] = src[i];
			i++;
			j++;
			dest[j] = src[i];
			j++;
			dest[j] = ' ';
		}
		else if (single_operator_check(src[i]))
		{
			ft_op_separator(&dest[j], &src[i], &i, &j);
			// dest[j] = ' ';
			// j++;
			// dest[j] = src[i];
			// j++;
			// dest[j] = ' ';
		}
		else
			dest[j] = src[i];
		if (src[i] != '\0')
		{
			i++;
			j++;
		}
	}
	dest[j] = '\0';
	ft_printf("real len of cleaned input: %i\n", ft_strlen(dest));
	return (dest);
}

/**
 * @brief function that 
 * 1st creates an array of strings out of the cleaned input
 * 2nd creates a linked list out of this array of strings --> TO-DO
 * 
 * @param readline_str the input of command line read by function readline
 * @return: a linked list with all input keywords or an array of strings???
 */
char	**create_nodes(char *readline_input)
{
	char	*clean_input;
	char	**input_arr;
	// t_token	token;

	clean_input = NULL;
	input_arr = NULL;
	clean_input = ft_clean_input(readline_input);
	if (!clean_input)
	{
		//TODO: error_handling;
		exit (EXIT_FAILURE);
	}
	input_arr = ft_split_quotes(clean_input, ' ');
	free(clean_input);
	clean_input = NULL;
	if (!input_arr)
	{
		//TODO: error_handling;
		exit (EXIT_FAILURE);
	}
	//TO-DO: create a linked list
	return (input_arr);
}
