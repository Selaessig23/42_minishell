#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the inbuilt-function "unset"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * This function counts a number of characters in a given string
 * up to the given character 'up_to'
*/
size_t	count_till_char(char *str, char up_to)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] && str[i] != up_to)
	{
		i++;
		count = i;
	}
	return (count);
}

/**
 * Function check if the variable given by argument is in t_big in envp.
*/
static int	uns_check_var(char **env, char *arg)
{
	size_t	env_str;
	size_t	arg_str;
	int		i;

	i = 0;
	arg_str = ft_strlen(arg);
	while (env[i])
	{
		env_str = count_till_char(env[i], '=');
		if (arg_str == env_str)
		{
			if (!ft_strncmp(env[i], arg, arg_str))
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief function to execute the builtin function "unset"
 * 
 * @param big big big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
int	ft_unset(t_big *big, t_data *comm_info)
{
	char	**cmd_arg;
	size_t	a;

	cmd_arg = comm_info->cmd;
	a = 1;
	while (cmd_arg[a] != NULL)
	{
		if (uns_check_var(big->env, cmd_arg[a]))
			ft_rmv_var_array(big, cmd_arg[a]);
		a++;
	}
	big->exit_code = 0;
	return (0);
}
