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
 * (the 1st char of this string (=quote) was already ignored)
 * @param sign the kind of quotation marks that are used (single or double)
*/
static int	ft_quote_remover(char *value_new, char *value_old, char sign)
{
	int	i;

	i = 0;
	while (value_old[i] && value_old[i] != sign)
	{
		value_new[i] = value_old[i];
		i += 1;
	}
	if (value_old[i] && value_old[i] == sign)
	{
		while (value_old[i + 1])
		{
			value_new[i] = value_old[i + 1];
			i += 1;
		}
	}
	return (i);
}

/**
 * @brief this functions deletes quotation marks at the beginning and end of
 * the value of token 21 / 22 / 27 / 28
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
	value_new = ft_calloc(((ft_strlen(value_old) - 2) + 1), 
			sizeof(char));
	if (value_old[i] == '\"')
		i = ft_quote_remover(value_new, &value_old[i + 1], '\"');
	else if (value_old[i] == '\'')
		i = ft_quote_remover(value_new, &value_old[i + 1], '\'');
	value_new[i] = '\0';
	temp->value = value_new;
	// printf ("Calloc: %lu, real: %zu\n, i: %i\n",
		// ((ft_strlen(value_old) - 2)), ft_strlen(value_new), i);
	free(value_old);
}
