#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be extended with
 * content from env
 */

/**
 * @brief helper function for add_env_to_value 
 * that integrates the env-value to new string
 * and returns the counter j to be able to proceed with
 * in add_env_to_value
 * 
 * @param value_new the tokens value that has to be adapted
 * @param env the env-value that has to be inserted
 */
static int	ft_add_env(char *value_new, char *env)
{
	char	*temp;
	int		j;

	j = 0;
	temp = value_new;
	while (*env)
	{
		*temp = *env;
		j += 1;
		env += 1;
		temp += 1;
	}
	return (j);
}


/**
 * @brief function that adds required envp-variable to value
 * 
 * @param value_old	the value of the command line input token that has
 * to be adapted
 * @param env	value of env variable
 * @param env_name env variable name, starting with $
 */
char	*add_env_to_value(char *value_old, char *env, char *env_name)
{
	char	*value_new;
	int	i;
	int	j;
	
	//(env + 1) to exclude the variable's name + '='
	i = (ft_strlen(value_old) + ft_strlen(&(*(env + 1))));
	value_new = ft_calloc(i, sizeof(char));
	if (!value_new)
		error_handling(2);
	//add new content of env to value at point of $variablename
	//could NOT create problems when having same env-variable several times as it only checks for 1st occurance, 
	//NO: all $-signs are already cleaned / extended
	i = 0;
	j = 0;
	// printf("test 3A: %s\nvalue_old: %s\n", (env), value_old);
	while (value_old[i] && (!ft_strnstr(&(value_old[i]), env_name, ft_strlen(env_name))))
	{
		value_new[i] = value_old[i];
		i++;
	}
	j = ft_add_env(&value_new[i], env);
	// while (*env)
	// {
	// 	value_new[i + j] = *env;
	// 	j++;
	// 	env++;
	// }
	while (value_old[i + ft_strlen(env_name)])
	{
		value_new[i + j] = value_old[i + ft_strlen(env_name)];
		i++;
	}
	value_new[i + j] = '\0';
	// printf("test 4A\n");
	return (value_new);
}
