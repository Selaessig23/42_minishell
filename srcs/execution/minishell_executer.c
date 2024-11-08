#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the incrementation of 
 * env-variable $SHLVL in case of executing minishell
 * within a minishell-environment is handled
 */

/**
 * @brief function to convert existing SHLVL-value into a number
 */
size_t	ft_shlvl_converter(char *shlvl_old)
{
	int	i;

	i = 0;
	while (shlvl_old[i])
	{
		if (!ft_isdigit(shlvl_old[i]) && shlvl_old[i] != '-'
			&& shlvl_old[i] != '+')
			return (0);
		i += 1;
	}
	return (ft_atoi(shlvl_old));
}

/**
 * @brief function to execute the builtin function "exit", 
 * it closes the programm and frees all allocated memory
 * 
 * @param env an array of strings with all environmental variables
 */
void	ft_ms_executer(char *env[])
{
	char	*temp;
	char	*shlvl_new;
	char	*count_new;
	int		count;

	count = 0;
	while (*env && ft_strncmp("SHLVL", *env, 4))
		env++;
	temp = *env;
	// printf("test 2a: temp = %s\n", temp + 6);
	count = ft_shlvl_converter(temp + 6);
	// printf("test: %i", count);
	if (count < 0)
		count = 0;
	else 
		count += 1;
	// printf("test 2b: count = %zu\n", count);
	count_new = ft_itoa(count);
	if (!count_new)
		error_handling(1);
	shlvl_new = ft_strjoin("SHLVL=", count_new);
	if (!shlvl_new)
		error_handling(1);
	free(count_new);
	// printf("test 2c: env new = %s\n", shlvl_new);
	*env = shlvl_new;
	free (temp);
}
