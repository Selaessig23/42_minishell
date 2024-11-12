/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:48:19 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 14:48:22 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be extended with
 * content from env if the $-varname matches an env-variable
 * or $+varname will be deleted if not
 */

/**
 * @brief function to cut (at '=') the variable values of env to
 * only use the varnames and return this new array of string
 * 
 * function ft_is_env_var is located in expander_utils.c
 * 
 * @param env the array with all environment variables that have to be cutted
 * to var_name only
*/
static char	**ft_env_varname_creator(char **env)
{
	char	**env_var_names;
	char	**env_var_names_save;
	char	*env_value;
	int		i;

	i = 0;
	env_var_names = ft_calloc((ft_arrlen(env) + 1), sizeof(char *));
	env_var_names_save = env_var_names;
	while (env && *env)
	{
		i = 0;
		env_value = *env;
		while (env_value[i] && ft_is_env_var(env_value[i]))
			i += 1;
		if (env_value[i] == '=')
		{
			*env_var_names = ft_substr(*env, 0, i);
			if (!*env_var_names)
				error_handling(2);
		}
		env_var_names += 1;
		env += 1;
	}
	*env_var_names = NULL;
	return (env_var_names_save);
}

/**
 * @brief function that checks if the &keywords (var_name) is part of envp
 * 
 * @param value_old the value of the command line input token that has
 * to be adapted
 * @param var_name potential env variable name, starting with $
 * @param env the environment variables of minishell that have to be checked for
 */
static char	*ft_var_envchecker(char *value_old, char *var_name, char **env)
{
	char	**env_var_names;
	char	**env_var_names_save;

	env_var_names = ft_env_varname_creator(env);
	if (!env_var_names)
		error_handling(2);
	env_var_names_save = env_var_names;
	while (env_var_names && *env_var_names)
	{
		if (!ft_strncmp(*env_var_names, 
				(var_name + 1), ft_strlen(*env_var_names))
			&& (ft_strlen(*env_var_names) == ft_strlen (var_name + 1)))
		{
			ft_free(env_var_names_save);
			return (add_env_to_value(value_old, 
					(*env + (ft_strlen(var_name + 1) + 1)), var_name));
		}
		env_var_names++;
		env++;
	}
	ft_free(env_var_names_save);
	return (delete_varname_from_value(value_old, var_name));
}

/**
 * @brief helper function for ft_var_creator that counts the length of the
 * possibly env-var 
 * 
 * @param value_old the value of the command line input token that has
 * to be adapted
 */
static int	ft_var_cutter(char *value_old)
{
	int	i;

	i = 1;
	while (value_old[i]
		&& !((value_old[i] >= 9 && value_old[i] <= 13)
			|| (value_old[i] == ' ')
			|| !(ft_isalnum(value_old[i]))))
		i++;
	return (i);
}

/**
 * @brief function that extends the tokens' value with env infos
 * by searching for 1st occurance of $ and the following variable name,
 * than sending this to ft_extender
 * 
 * @param value_old the value of the command line input token that has
 * to be adapted
 * @param env the environment variables of minishell that have to be checked for
 */
char	*ft_var_creator(char *value_old, char **env)
{
	char	*temp;
	char	*value_new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	value_new = NULL;
	while (value_old[i])
	{
		if (value_old[i] == '$')
		{
			k = i;
			i += ft_var_cutter(&value_old[i]);
			temp = ft_substr(value_old, k, (i - k));
			if (!temp)
				error_handling(2);
			value_new = ft_var_envchecker(value_old, temp, env);
			free(temp);
			return (value_new);
		}
		i++;
	}
	return (value_old);
}
