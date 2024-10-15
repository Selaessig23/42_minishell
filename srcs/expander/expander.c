#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file the cleaning and extension of specific strings will
 * be organised
 */

/**
 * @brief function that checks if there is a $-sign within the 
 * specific string sent by ft_expa_precond and send the string 
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
		if (value_old[i + 1] && value_old[i] == '$'
			&& !((value_old[i + 1] == '$') || (value_old[i + 1] == ' ')))
		{
			if (value_old[i + 1] == '?')
				value_new = ft_exit_expander(value_old, big->exit_code);
			else
			{
				value_new = ft_var_creator(value_old, big->env);
				if (!*value_new)
				{
					ft_dprintf("The expantion is empty. I assign an exitcode 0\n");
					big->exit_code = 0;
				}
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
			ft_quote_checker(&curr->content);
		else if ((((t_lexer *)curr->content)->token == 25)
			|| (((t_lexer *)curr->content)->token == 26))
			ft_q_word_handling(&curr->content, big);
		if ((((t_lexer *)curr->content)->token == 20)
			|| (((t_lexer *)curr->content)->token == 21)
			|| (((t_lexer *)curr->content)->token == 25))
			ft_var_checker(&curr->content, big);
		curr = curr->next;
	}
}
