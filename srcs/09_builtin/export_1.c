/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:44:08 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/19 14:50:10 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION
 * it's a first file of the built-in command "export"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * The function is a helper fuction for 'exp_create' function.
 * It inserts a string 'str_to_add' into an array of strings.
 * It copies all strings from 'array_old' into 'array_new' and inserts
 * the new string at the end. It doesn't free anything. 
 * It doesn't re-assign any pointers.
 * All pointers reassigning or freeing must be done outside.
*/
char	**ft_add_arr_back(char *str_to_add,
	char **array_old, char **array_new)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = ft_arrlen(array_old);
	array_new = (char **)malloc(sizeof(char *) * (count + 2));
	if (!array_new)
		error_and_exit(2);
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
		error_and_exit(2);
	i += 1;
	array_new[i] = NULL;
	return (array_new);
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
// execution IF exe is true
// if exe is false - checking for errors and exit assigns exit code
int	ft_export_exe(t_big *big, t_data *comm_info)
{
	char	**cmd_arg;
	size_t	a;

	cmd_arg = comm_info->cmd;
	a = 1;
	while (cmd_arg[a] != NULL)
	{
		if (*cmd_arg[a] == '=' || ft_isdigit(*cmd_arg[a]))
			ft_dprintf("bash: export: `%s': not a valid identifier\n",
				cmd_arg[a]);
		else if (check_dash_in_var_name(cmd_arg[a]))
			ft_dprintf("bash: export: `%s': not a valid identifier\n",
				cmd_arg[a]);
		else if (big->exe == true)
		{
			if (!exp_check_var(big->env, cmd_arg[a]))
				exp_create(big, cmd_arg[a]);
			else if (exp_check_var(big->env, cmd_arg[a]))
				exp_replace_val(big, cmd_arg[a]);
		}
		a++;
	}
	big->exit_code = 0;
	export_exit_status(big, cmd_arg);
	return (0);
}

/**
 * @brief function to check if the command has an argument or not
 * if not --> simply sort env-vars in alphabetical order (ft_export_sort)
 * if yes --> execute the export-function (ft_export_exe)
 * 
 * @param big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
int	ft_export(t_big *big, t_data *comm_info)
{
	char	**cmd_arg;

	cmd_arg = comm_info->cmd;
	if (cmd_arg && *cmd_arg
		&& !ft_strncmp (cmd_arg[0], "export", ft_strlen("export"))
		&& ft_strlen("export") == ft_strlen(cmd_arg[0])
		&& ft_arrlen(cmd_arg) == 1)
		ft_export_sort(big);
	else if (cmd_arg && *cmd_arg)
		ft_export_exe(big, comm_info);
	return (0);
}
