
#include "minishell.h"

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
 * @brief function that counts the amount of operators
 *  
 */
static int	ft_count(char *src)
{
	int	len;

	len = 0;
	while (*src)
	{
		if (*src == '\"')
		{
			len++;
			src++;
			while (*src && *src != '\"')
			{
				len++;
				src++;
			// len += 1;
			}
		}
		else if (*src == '\'')
		{
			len++;
			src++;
			while (*src && *src != '\'')
			{
				len++;
				src++;
			// len += 1;
			}
		}
		if (double_operator_check(*src, (*src + 1)))
		{
			len += 4;
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
			// dest[j++] = ' ';
			// j++;
			dest[j] = src[i];
			// ft_printf("test\n");
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
				// i++;
				// j++;
				while (src[i] && src[i] != '\"')
					dest[j++] = src[i++];
				// dest[j++] = src[i];
				if (src[i] != '\0')
					dest[j] = src[i];
			}
			// j++;
			// dest[j] = ' ';
		}
		else if (src[i] == '\'')
		{
			// dest[j] = ' ';
			// j++;
			dest[j] = src[i];
			// j++;
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
				// dest[j++] = src[i];
				if (src[i] != '\0')
					dest[j] = src[i];
			}
			// dest[j] = ' ';
		}
		// else if (src[i] == '\'')
		// {
		// 	dest[j] = src[i];
		// 	while (src[++i] && src[i] != '\'')
		// 		dest[++j] = src[i];
		// 	dest[j] = src[i];
		// 	i++;
		// 	j++;
		// 	dest[j] = src[i];
		// 	i++;
		// 	j++;
		// }
		else if (double_operator_check(src[i], src[i + 1]))
		{
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
			dest[j] = ' ';
			j++;
			dest[j] = src[i];
			j++;
			dest[j] = ' ';
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
 * 2nd creates a linked list out of this array of strings
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
	return (input_arr);
}