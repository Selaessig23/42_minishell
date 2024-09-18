#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be cleaned and extended with
 * special content if there is $, which serves as sign for var-start
 */

/**
 * @brief 
 * 
 * @param value_new the new value that should replace value_old
 * @param value_old the old value belonging to one of the quoted-token
 * @param sign the kind of quotation marks that are used (single or double)
*/
static int	ft_quote_remover(char **temp, char *value_old, char sign)
{
	int		i;
	int		j;
	char	*value_new;

	i = 0;
	j = 0;
	value_new = *temp;
	while (value_old[j])
	{
		if (value_old[j] != sign)
		{
			value_new[i] = value_old[j];
			i += 1;
		}
		j += 1;
	}
	// if (value_old[j - 1] == sign)
	// 	i += 1;
	value_new[i] = '\0';
	return (i);
}

/**
 * @brief helper function for ft_quote_check that counts
 * the amount of specific qoutes
 * 
 * @param 
 */
int	ft_quotes_counter(t_tokentype token, char *value_old)
{
	int	i;

	i = 0;
	if (token == 21 || token == 25)
	{
		while (*value_old)
		{
			if (*value_old == '\"')
				i += 1;
			value_old += 1;
		}
	}
	else if (token == 22 || token == 26)
	{
		while (*value_old)
		{
			if (*value_old == '\'')
				i += 1;
			value_old += 1;
		}
	}
	return (i);
}

/**
 * @brief this functions deletes quotation marks at the beginning and end of
 * the value of token 21 / 22 / 25 / 26
 * 
 * DO I HAVE TO ENSURE THAT value_old has enough characters to remove quotes?
 * 
 * @param token node of token-list that has to be cleaned from quotes
 */
void	ft_quote_checker(void **token)
{
	char	*value_new;
	t_lexer	*temp;
	char	*value_old;
	int		i;

	i = 0;
	temp = *token;
	value_old = temp->value;
	value_new = ft_calloc(((ft_strlen(value_old) - 
					ft_quotes_counter(temp->token, value_old)) + 1), 
			sizeof(char));
	// printf("\ncalloc: %lu\n", (ft_strlen(value_old) - ft_quotes_counter(temp->token, value_old)));
	if (temp->token == 21 || temp->token == 25)
		i = ft_quote_remover(&value_new, value_old, '\"');
	else if (temp->token == 22 || temp->token == 26)
		i = ft_quote_remover(&value_new, value_old, '\'');
	temp->value = value_new;
	// printf ("Calloc: %lu, real: %zu\n, i: %i\n",
		// ((ft_strlen(value_old) - 2)), ft_strlen(value_new), i);
	free(value_old);
}
