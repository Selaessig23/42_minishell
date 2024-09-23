#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the inbuilt-function "pwd"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to print all env-variables
 * 
 * TODO: set exit status in struct big after execution
 * 
 * @param big big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed in case of builtin exit
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
	big->exit_code = 1;
}
