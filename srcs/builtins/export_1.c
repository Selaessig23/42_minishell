#include "minishell.h"

/**
 * DESCRIPTION
 * it's a first file of the built-in command "export"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * The function is a helper fuction for 'exp_create' function.
 * It inserts a string 'str_to_add' into a array of strings.
 * It copies all strings from 'array_old' into 'array_new' and inserts
 * a new string. It doesn't free anything. It doesn't re-assign any pointers.
 * All pointers reassigning or freeing must be done outside.
*/
static char	**ft_add_arr_back(char *str_to_add,
	char **array_old, char **array_new)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = ft_arrlen(array_old);
	array_new = (char **)malloc(sizeof(char *) * (count + 2));
	if (!array_new)
		error_handling(2);
	if (count > 0)
	{
		while (array_old[i] != NULL)
		{
			array_new[i] = ft_strdup(array_old[i]);
			i++;
		}
	}
	array_new[i] = ft_strdup(str_to_add);
	if (!array_new[i])
		error_handling(2);
	i += 1;
	array_new[i] = NULL;
	return (array_new);
}

/**
 * The function replaces the old value of the environmental
 * variable to the new one.
 * @param var_to_rmv is a string with only a name of environmental
 * variable, it is retrived from a 'str_new_val'
 * @param str_new_val is a string as an argument for export command
 * which contains a variable that is already in env array and also either
 * consist of '=' and following characters or only '=' sign.
 */
static void	exp_replace_val(t_big *big, char *str_new_val)
{
	char	**old;
	char	**new;
	char	**var_to_rmv;

	new = NULL;
	old = NULL;
	var_to_rmv = ft_split(str_new_val, '=');
	ft_rmv_var_array(big, var_to_rmv[0]);
	ft_free(var_to_rmv);
	old = big->env;
	new = ft_add_arr_back(str_new_val, old, new);
	big->env = new;
	if ((old))
		ft_free(old);
}

/**
 * This function inserts a new variable to an array of strings 'ENV'.
 * It calls the function 'ft_add_arr_back' that insert a new string into
 * a new array of string. Also this function assign a new pointer to 
 * 'char **env' in t_big *big, and it frees an old array of strings.
 * @param str_to_add - a new string to insert
 * @param big - a structure contains an array of strings 'env' of
 * current environmantal variables.
*/
static void	exp_create(t_big *big, char *str_to_add)
{
	char	**old;
	char	**new;

	new = NULL;
	old = big->env;
	new = ft_add_arr_back(str_to_add, old, new);
	big->env = new;
	if ((old))
		ft_free(old);
}

/**
 * Function checks if the variable given by argument is in t_big in envp.
 * It takes characters till '=' sign and compare it to each string in envp,
 * considering characters till '=' sign. In case of succes return 1,
 * otherwise it returns 0.
*/
static int	exp_check_var(char **env, char *arg)
{
	size_t	env_str;
	size_t	arg_str;
	int		i;

	i = 0;
	arg_str = count_till_char(arg, '=');
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
 * @brief function to execute the builtin function "export"
 * 
 * @param big big big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
int	ft_export(t_big *big, t_data *comm_info)
{
	char	**cmd_arg;
	size_t	i;
	size_t	a;

	cmd_arg = comm_info->cmd;
	i = 0;
	a = 1;
	while (cmd_arg[a] != NULL)
	{
		if (ft_strchr(cmd_arg[a], '='))
		{
			if (*cmd_arg[a] == '=')
				ft_printf("-bash: export: `%s': not a valid identifier\n",
					cmd_arg[a]);
			else if (!exp_check_var(big->env, cmd_arg[a]))
				exp_create(big, cmd_arg[a]);
			else if (exp_check_var(big->env, cmd_arg[a]))
				exp_replace_val(big, cmd_arg[a]);
		}
		else if (!ft_strchr(cmd_arg[a], '='))
			big->exit_code = 0;
		a++;
	}
	export_exit_status(big, cmd_arg);
	return (0);
}
