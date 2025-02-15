/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:48:30 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 20:14:05 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION
 * in this second file of the built-in command "export"
 */
/**
 * The function check the argument for invalid case
 * with a '-' in the name of the variable.
 * For instance, "export HELLO-=123".
*/
int	check_dash_in_var_name(char *argument)
{
	char	**checker;
	int		i;

	i = 0;
	checker = ft_split(argument, '=');
	if (ft_strchr(checker[0], '-'))
		i = 1;
	ft_free(checker);
	return (i);
}

/**
 * EXIT_STATUS checker for EXPORT built-in.
 * If ANY of the arguments starts with '=' then
 * 'exit_code' is 1, if no error it is 0.
 */
void	export_exit_status(t_big *big, char **cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i])
	{
		if (*cmd_arg[i] == '=' || ft_isdigit(*cmd_arg[i])
			|| check_dash_in_var_name(cmd_arg[i]))
		{
			big->exit_code = 1;
			return ;
		}
		i++;
	}
}

/**
 * It's a part of ft_rmv_var_array functin which removes
 * a string with a specific variable.
 * 
 * The function compares characters in the two strings up
 * to the first occurence of '=' character in 'org_env'.
 * If the VALUES in ENV and ARGUMENT VALUE match,
 * it returns 1, otherwise - 0.
 * @param org_env - an original string from ENV array.
 * @param arg_rm - a string containing the variable to be removed.
 * @param c - a character that we consider a separator for comparison.
 * In case of working with environmental varibale, this is always '=' sign.
*/
static int	same_var(char *org_env, char *arg_rmv, char c)
{
	size_t	env_sz;
	size_t	arg_sz;

	env_sz = count_till_char(org_env, c);
	arg_sz = ft_strlen(arg_rmv);
	if (env_sz == arg_sz)
	{
		if (!ft_strncmp(org_env, arg_rmv, arg_sz))
			return (1);
	}
	return (0);
}

/**
 * It's just a part of 'ft_rmv_var_array' function
 * to comply with the 25-line rule.
 */
static void	ft_rmv_var_array_2(char **array_old,
	char **array_new, char *str_to_rmv)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	{
		while (array_old[i] != NULL)
		{
			if (!same_var(array_old[i], str_to_rmv, '='))
			{
				array_new[j] = ft_strdup(array_old[i]);
				j++;
			}
			i++;
		}
	}
	array_new[j] = NULL;
}

/**
 * This function is a part of biuilt-in UNSET and EXPORT.
 * It removes a string with a given variable from 'ENV' array of strings.
 * 1. It creates a new array of strings 'array_new',
 * 2. it copies each string from old array of strings
 * that represents ENV (environmental variable), except of
 * the one string that identical with 'str_to_rmv' up to '='
 * character.
*/
void	ft_rmv_var_array(t_big *big, char *str_to_rmv)
{
	char	**array_new;
	char	**array_old;
	size_t	count;

	array_old = big->env;
	count = ft_arrlen(array_old);
	array_new = (char **)malloc(sizeof(char *) * (count));
	if (!array_new)
		error_and_exit(2);
	if (count > 0)
		ft_rmv_var_array_2(array_old, array_new, str_to_rmv);
	big->env = array_new;
	if (array_old)
		ft_free(array_old);
}
