#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the q_words-tokens will be cleaned and extended with
 * special content if there is $, which serves as sign for var-start
 * q_words-tokens are special in that kind, that they have to consider
 * several quotation types within one large string. depending on them, 
 * $-variables have to be considered (if in double quote part) or not
 * (if in single quote part), e. g. hello"this"isa'$single'thisa"$double"
 */

/**
 * @brief function that transforms an array of strings to a 
 * single string
 * 
 * !!!CHANGE strcpy TO ft_strcpy!!!
 * 
 * @param arr the array of strings to read from
 */
char	*ft_listtostr(t_list *q_word_list)
{
	t_list	*curr;
	char	*curr_str;
	char	*str;
	int		count_list;
	int		count_str;
	// int		i;
	int		j;

	curr = q_word_list;
	curr_str = ((t_lexer *)curr->content)->value;
	count_list = 0;
	count_str = 0;
	j = 0;
	while (curr != NULL)
	{
		curr_str = ((t_lexer *)curr->content)->value;
		count_str += ft_strlen(curr_str);
		curr = curr->next;
	}
	str = ft_calloc(((count_str) + 1), sizeof(char));
	curr = q_word_list;
	while (curr != NULL)
	{
		curr_str = ((t_lexer *)curr->content)->value;
		j = ft_strlen(str);
		strcpy(&str[j], curr_str);
	}
	str[ft_strlen(str) + 1] = '\0';
	return (str);
}

/**
 * @brief function that creates and array of strings
 * out of the q_word to better handle the q_word-tokens
 * 
 * @param value_old the char to count 
 * cut and transferred to array of strings 
 * (in parts of single quotes | double quotes | no quotes)
 * @param p_value_new the malloced array of strings to copy in
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
		{
			j = i;
			i += 1;
			while (value_old[i] && value_old[i] != '\'')
				i += 1;
		}
		else if (value_old[i] == '\"')
		{
			j = i;
			i += 1;
			while (value_old[i] && value_old[i] != '\"')
				i += 1;
		}
		else
		{
			j = i;
			i += 1;
			while (value_old[i] 
				&& value_old[i] != '\'' && value_old[i] != '\"')
				i += 1;
		}
		*value_new = ft_substr(value_old, j, i);
		value_new += 1;
		if (value_old[i] == '\'' || value_old[i] == '\"')
			i += 1;
	}
	*value_new = NULL;
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

	counter = 0;
	while (*value_old)
	{
		if (*value_old == '\'')
		{
			counter += 1;
			value_old += 1;
			while (*value_old && *value_old != '\'')
				value_old += 1;
		}
		else if (*value_old == '\"')
		{
			counter += 1;
			value_old += 1;
			while (*value_old && *value_old != '\"')
				value_old += 1;
		}
		else
		{
			counter += 1;
			value_old += 1;
			while (*value_old && *value_old != '\'' && *value_old != '\"')
				value_old += 1;
		}
		if (*value_old == '\'' || *value_old == '\"')
			value_old += 1;
	}
	return (counter);
}

/**
 * @brief this functions organises the special treatment of
 * values of token 25 / 26
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
	// int		counter;
	t_list	*q_word_list;

	printf("test\n");
	temp = *token;
	value_old = temp->value;
	help_arr = ft_calloc((ft_q_counter(value_old) + 1), sizeof(char *));
	ft_q_arr_creator(value_old, &help_arr);
	q_word_list = ft_tokenizer(help_arr);
	ft_free(help_arr);
	ft_expa_precond(q_word_list, big);
	value_new = ft_listtostr(q_word_list);
	ft_free_ll(&q_word_list);
	temp->value = value_new;
	free(value_old);
}
