#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be extended with
 * content from env if the $-varname matches an env-variable
 * or $+varname will be deleted if not
 */

/**
 * @brief function to cut (at '=') the varnames of env out of env
 * 
 * find ft_is_env_var in expander_utils.c
 * 
 * @param env the array with all environment variables that have to be cutted
 * to var_name only
*/
static char **ft_env_varname_creator(char **env)
{
	char	**env_var_names;
	char	**env_var_names_save;
	char 	*env_value;
	int		i;
	// int		j;

	i = 0;
	// j = 0;
	env_var_names = ft_calloc((ft_arrlen(env) + 1), sizeof(char *));
	env_var_names_save = env_var_names;
	while (env && *env)
	{
		i = 0;
		// j = 0;
		env_value = *env;
		// printf("env_value: %s\n", env_value);
		while(env_value[i] && ft_is_env_var(env_value[i]))
		{
			// (*env) += 1;
			i += 1;
		}
		// printf("char_check 1: %c\n", **env);
		if (env_value[i] == '=')
		{
			*env_var_names = ft_substr(*env, 0, i);
			if (!*env_var_names)
				error_handling(2);
		}
		// printf("env_var_name: %s\n", *env_var_names);
		env_var_names += 1;
		env += 1;
	}
	*env_var_names = NULL;
	return (env_var_names_save);
}

/**
 * @brief function that checks if the &keywords is part of envp
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
	// printf("env variable name: %s\nlength: %zu\n", (var_name + 1), ft_strlen(var_name + 1));
	while (env_var_names && *env_var_names)
	{
		// printf("test 2A: %s\n", *env_var_names);
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
	// printf("test2B\n");
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
			// i++;
			i += ft_var_cutter(&value_old[i]);
			// while (value_old[i]
			// 	&& !((value_old[i] >= 9 && value_old[i] <= 13)
			// 		|| (value_old[i] == ' ')
			// 		|| !(ft_isalnum(value_old[i]))))
			// 	i++;
			temp = ft_substr(value_old, k, (i - k));
			// printf("Variable name to search for: %s\n", temp);
			if (!temp)
				error_handling(2);
			value_new = ft_var_envchecker(value_old, temp, env);
			free(temp);
			// printf("test 5\n");
			return (value_new);
		}
		i++;
	}
	return (value_old);
}
