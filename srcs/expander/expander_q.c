#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the q_words-tokens will be cleaned and extended with
 * special content if there is $ in parts without quotes or within double-quotes, 
 * nothing will be extended if in parts with single-quotes. 
 * q_words-tokens are special in that kind, that they they can consist of
 * several types of strings (with single quotes / double quotes / no quotes) 
 * within one large string. depending on the kind
 * of quotation mark, $-variables have to be considered 
 * (if in double quote part or in parts without a quote) 
 * or not (if in single quote part), e. g. hello"this"isa'$single'thisa"$double"
 */

/**
 * @brief function to copy from src to dest
 * 
 * @param dest the string to copy in
 * @param src the string to copy from
 */
char	*ft_strcpy(char *dest, const char *src)
{
	if (!src)
		return (NULL);
	while (*src)
	{
		*dest = *src;
		dest += 1;
		src += 1;
	}
	return (dest);
}

/**
 * @brief helper function for ft_listtostr to count the
 * size of each string of the linked list
 * 
 * @param q_word_list the linked list in wich the strings of 
 * (void) content have to be counted
 */
size_t	ft_count_str_in_ll(t_list *q_word_list)
{
	t_list	*curr;
	char	*str_to_count;
	size_t	count_str;

	curr = q_word_list;
	count_str = 0;
	while (curr != NULL)
	{
		str_to_count = ((t_lexer *)curr->content)->value;
		count_str += ft_strlen(str_to_count);
		curr = curr->next;
	}
	return (count_str);
}

/**
 * @brief function that transforms an array of strings to a 
 * single string
 *  
 * @param arr the array of strings to read from
 */
char	*ft_listtostr(t_list *q_word_list)
{
	t_list	*curr;
	char	*str;
	int		count_str;
	int		j;

	// printf("testA\n");
	curr = q_word_list;
	count_str = ft_count_str_in_ll(q_word_list);
	j = 0;
	// printf("count_str: %i\n", count_str);
	str = ft_calloc(((count_str) + 1), sizeof(char));
	curr = q_word_list;
	while (curr != NULL)
	{
		j = ft_strlen(str);
		ft_strcpy(&str[j], ((t_lexer *)curr->content)->value);
		// str = ft_strcpy(str, ((t_lexer *)curr->content)->value);
		curr = curr->next;
	}
	str[count_str] = '\0';
	return (str);
}

/**
 * @brief helper function for ft_q_arr_creator, it iteraters 
 * through the value_old string until next " / ' is found and
 * sets values of j (start of string-part) and i (end of string-part)
 * 
 * @param p_counter pointer to the counter
 * @param p_i pointer to iterator of value_old
 * @param value_old the char to itorate over
 * @param sign the sign to check for (' / " / 9 -->
 * 9 stands for not ' or ")
*/ 
static void	ft_q_arrcreat_helper(int *j, int *i,
	char *value_old, char sign)
{
	*j = *i;
	if (sign == '\'' || sign == '\"')
	{
		*i += 1;
		while (value_old[*(i)] && value_old[*(i)] != sign)
			*(i) += 1;
	}
	else
	{
		if (value_old[*(i) + 1]
			&& !(value_old[*(i) + 1] == '\'' || value_old[*(i) + 1] == '\"'))
			*i += 1;
		while (value_old[*(i)] && value_old[*(i) + 1] 
			&& !(value_old[*(i) + 1] == '\'' || value_old[*(i) + 1] == '\"'))
			*(i) += 1;
	}
}


/**
 * @brief function that creates and array of strings
 * out of the q_word to better handle the q_word-tokens
 * 
 * @param value_old the char to count 
 * cut and transferred to array of strings 
 * (in parts of single quotes | double quotes | no quotes)
 * @param p_value_new pointer to the malloced array of strings to copy in
 */
void	ft_q_arr_creator(char *value_old, char ***p_value_new)
{
	int		i;
	int		j;
	char	**value_new;

	i = 0;
	j = 0;
	value_new = *p_value_new;
	while (value_old[i])
	{
		if (value_old[i] == '\'')
			ft_q_arrcreat_helper(&j, &i, value_old, '\'');
		else if (value_old[i] == '\"')
			ft_q_arrcreat_helper(&j, &i, value_old, '\"');
		else
			ft_q_arrcreat_helper(&j, &i, value_old, 'X');
		*value_new = ft_substr(value_old, j, ((i + 1) - j));
		// printf("value_new = %s\n", *value_new);
		value_new += 1;
		if (value_old[i])
			i += 1;
	}
	*value_new = NULL;
}

/**
 * @brief helper function for ft_q_counter, it iterates
 * through the string until next " or ' is found * 
 * 
 * @param p_counter pointer to the counter
 * @param p_i pointer to iterator of value_old
 * @param value_old the char to itorate over
 * @param sign the sign to check for
*/ 
static void	ft_q_count_helper(int *counter, int *i,
	char *value_old, char sign)
{
	*(counter) += 1;
	*i += 1;
	while (value_old[*(i)] && value_old[*(i)] != sign)
		*(i) += 1;
}


/**
 * @brief function to count the size of new array of strings
 * which is required to handle the q_word-tokens correctly
 * 
 * @param value_old the char to count 
 * (cut in parts of single quotes | double quotes | no quotes)
 */
int	ft_q_counter(char *value_old)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	while (value_old[i])
	{
		// printf("string: %s\n", &value_old[i]);
		if (value_old[i] == '\'')
		{
			// printf("case A\n");
			ft_q_count_helper(&counter, &i, value_old, '\'');
		}
		else if (value_old[i] == '\"')
		{
			// printf("case B\n");
			ft_q_count_helper(&counter, &i, value_old, '\"');
		}
		else
		{
			// printf("case C\n");
			counter += 1;
			if (value_old[i + 1] 
				&& !(value_old[i + 1] == '\'' || value_old[i + 1] == '\"'))
				i += 1;
			while (value_old[i] && value_old[i + 1] 
				&& !(value_old[i + 1] == '\'' || value_old[i + 1] == '\"'))
				i += 1;
		}
		if (value_old[i])
			i += 1;
	}
	// printf("counter says: %i\n", counter);
	return (counter);
}

/**
 * @brief this functions organises the special treatment of
 * values of token 25 / 26
 * 1) values of these tokens are transformed to an array of strings
 * 2) than this array will run through the tokenizer and expander
 * as if it would be a readline-input
 * 3) at the end this linked-list (q_word_list) will be transformed
 * to a string again and the adress of token 25/26 will be 
 * overwritten by this string, and a new tokentype (28) will be assigned, 
 * at very last old string will be freed
 * 
 * 
 * @param token node of token-list that has to be cleaned from quotes
 * @param big structure which contains the environmental variable array
 */
void	ft_q_word_handling(void **token, t_big *big)
{
	t_lexer	*temp;
	char	*value_old;
	char 	*value_new;
	char	**help_arr;
	t_list	*q_word_list;

	// printf("test1\n");
	temp = *token;
	value_old = temp->value;
	help_arr = ft_calloc((ft_q_counter(value_old) + 1), sizeof(char *));
	// printf("test2\n");
	ft_q_arr_creator(value_old, &help_arr);
	// printf("test3\n");
	q_word_list = ft_tokenizer(help_arr);
	ft_free(help_arr);
	// printf("test4\n");
	ft_expa_precond(q_word_list, big);
	// printf("test5\n");
	value_new = ft_listtostr(q_word_list);
	// printf("test6\n");
	ft_free_ll(&q_word_list);
	// printf("test7\n");
	temp->value = value_new;
	temp->token = 29;
	free(value_old);
}
