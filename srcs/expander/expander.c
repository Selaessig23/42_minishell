#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be cleaned and extended with
 * special content if there is $, which serves as sign for var-start
 */

/**
 * @brief function that checks if there is a $-sign within the 
 * specific string sent by ft_ext_precond and send the string 
 * to further functions according to the special parameter
 * 
 * $$, $#, $*, $@, $0, $1.., $[10].., $_, $!, $-, $, $$ are not
 * treated and therefor not seen as special character
 * except $env and $?
 * 
 * @param token node of token-list that has to be cleaned from quotes
 * @param big structure which contains the environmental variable array
 */
static void	ft_var_checker(void	**token, t_big *big)
{
	t_lexer	*temp;
	char	*value_new;
	char	*value_old;
	int		i;

	i = 0;
	temp = *token;
	value_new = NULL;
	value_old = temp->value;
	while (value_old[i])
	{
		if (value_old[i] == '$')
		{
			// if (value_old[i] == '$' && value_old[i + 1] == '?')
			if (value_old[i + 1] == '?')
			{
				value_new = ft_exit_expander(value_old, big->exit_code);
				// temp->value = value_new;
				// printf("test 6: %s\n", (temp->value));
				// free (value_old);
				// value_old = NULL;
				// value_old = temp->value;
			}
			// else if (value_old[i] == '$')
			else
			{
				value_new = ft_var_creator(value_old, big->env);
				// temp->value = value_new;
				// printf("test 6: %s\n", (temp->value));
				// free (value_old);
				// value_old = NULL;
				// value_old = temp->value;
			}
			temp->value = value_new;
			free (value_old);
			value_old = NULL;
			value_old = temp->value;
		}
		if (value_old[i])
			i += 1;
	}
}

/**
 * @brief this functions deletes quotation marks at the beginning and end of
 * the value of token single_quoted / double_quoted
 * 
 * DO I HAVE TO ENSURE THAT value_old has enough characters to remove quotes?
 * 
 * @param token node of token-list that has to be cleaned from quotes
 */
static void	ft_quote_remover(void **token)
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
	while (value_old[i + 1] && value_old[i + 1] != '\"') 
	{
		value_new[i] = value_old[i + 1];
		i += 1;
	}
	value_new[i] = '\0';
	temp->value = value_new;
	// printf ("Calloc: %lu, real: %zu\n",
		// ((ft_strlen(value_old) - 2)), ft_strlen(value_new));
	free(value_old);
}

/**
 * @brief function that organises the expansion and reduction
 * of command line input by checking for specific string tokens
 * 
 * MISSING, if we want to handle UNCLOSED QUOTES: delete them
 * 
 * @param lexx linked list with cleaned command line input and tokens
 * @param big structure which contains the environmental variable array
 */
void	ft_expa_precond(t_list *lexx, t_big *big)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if ((((t_lexer *)curr->content)->token == 21)
			|| (((t_lexer *)curr->content)->token == 22))
			ft_quote_remover(&curr->content);
		if ((((t_lexer *)curr->content)->token == 20)
			|| (((t_lexer *)curr->content)->token == 21))
			ft_var_checker(&curr->content, big);
		curr = curr->next;
	}
}
