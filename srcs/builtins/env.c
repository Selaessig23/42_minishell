#include "minishell.h"

/**
 * DESCRIPTION
 * 
 */

/**
 * 
 */
void	ft_print_env(t_big *big)
{
	char	**env_list;

	env_list = big->env;
	while (env_list && *env_list)
	{
		ft_printf("%s\n", *env_list);
		env_list += 1;
	}
}
