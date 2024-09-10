#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be extended with
 * content from env if the $-varname matches an env-variable
 * or $+varname will be deleted if not
 */

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
	// printf("env variable name: %s\nlength: %zu\n", (var_name + 1), ft_strlen(var_name + 1));
	while (env && *env)
	{
		// printf("test 2A: %s\n", *env);
		if (!ft_strncmp(*env, (var_name + 1), ft_strlen(var_name + 1)))
		{
			return (add_env_to_value(value_old, (*env + (ft_strlen(var_name + 1) + 1)), var_name));
		}
		env++;
	}
	// printf("test2B\n");
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
