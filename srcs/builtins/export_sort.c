/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:14:03 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/14 12:36:25 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * this file handles the sorting request of builtin "export" access
 * (if command line input == "export" without any arguments)
 */

/**
 * @brief helper function for ft_export_addquotes
 * that copies from value_old to value_new. integrating quotation marks
 * between the value of the env-var
 * 
 * @param env_cpy copy of array env that should be adapted
 */
static void	ft_export_addquotes_helper(char **p_env_var_new, char *env_var_old)
{
	int		i;
	char	*env_var_new;

	i = 0;
	env_var_new = *p_env_var_new;
	while (env_var_old[i] && env_var_old[i] != '=')
	{
		env_var_new[i] = env_var_old[i];
		i += 1;
	}
	env_var_new[i] = env_var_old[i];
	env_var_new[i + 1] = '\"';
	i += 1;
	while (env_var_old[i])
	{
		env_var_new[i + 1] = env_var_old[i];
		i += 1;
	}
	env_var_new[i + 1] = '\"';
	env_var_new[i + 2] = '\0';
}

/**
 * @brief this function adds quotation marks for alle values of
 * the env_variables
 * 
 * @param env_cpy copy of array env that should be adapted
 */
static void	ft_export_addquotes(char ***p_env_cpy)
{
	char	**env_cpy;
	char	*env_var_old;
	char	*env_var_new;

	env_cpy = *p_env_cpy;
	env_var_old = NULL;
	env_var_new = NULL;
	while (env_cpy && *env_cpy)
	{
		env_var_old = *env_cpy;
		env_var_new = ft_calloc((ft_strlen(env_var_old) + 3), sizeof(char));
		ft_export_addquotes_helper(&env_var_new, env_var_old);
		*env_cpy = env_var_new;
		free(env_var_old);
		env_cpy += 1;
	}
}

/**
 * @brief function to swap two pointers
 * 
 * @param a 1st pointer
 * @param b 2nd pointer
 */
static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief function to sort the array of env by
 * comparing two variable names and check if they
 * are sorted correctly, if not swap ans re-start 
 * checking the env-var-names from the beginning
 * 
 * @param env_cpy copy of array env that should be sorted
 */
static void	ft_export_sort_algo(char ***p_env_cpy)
{
	int		i;
	char	**env_cpy;

	env_cpy = *p_env_cpy;
	i = 0;
	while (env_cpy[i] && env_cpy[i + 1])
	{
		if (ft_strncmp(env_cpy[i], env_cpy[i + 1], ft_strlen(env_cpy[i])) > 0)
		{
			ft_swap(&env_cpy[i], &env_cpy[i + 1]);
			i = 0;
		}
		else
			i += 1;
	}
	ft_export_addquotes(p_env_cpy);
}

/**
 * @brief function to organise the sorting request of the 
 * builtin function "export"
 * (1) it creates a copy of env to print from
 * (2) it sorts 
 * (3) it prints
 * (4) it frees the copy
 * 
 * @param big struct which holds the env-variable inside
 */
void	ft_export_sort(t_big *big)
{
	char	**env_cpy;
	int		i;

	i = 0;
	if (big->exe == false)
		env_cpy = NULL;
	else
	{
		env_cpy = copy_envp(big->env);
		ft_export_sort_algo(&env_cpy);
		while (env_cpy[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(env_cpy[i], 1);
			i += 1;
		}
		ft_free(env_cpy);
	}
}
