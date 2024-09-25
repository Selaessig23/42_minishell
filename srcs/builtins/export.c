#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the inbuilt-function "export"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * This function counts a number of characters in a given string
 * up to the given character 'up_to'
*/
static size_t  count_till_char(char *str, char up_to)
{
    size_t  count;
    size_t     i;

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
 * The function compares characters in two strings up
 * to first occurence '=' character in 'org_env'.
 * If the VALUE in ENV and ARGUMENT VALUE are identical
 * it returns 1, otherwise - 0.
*/
static int same_var(char *org_env, char *arg_rmv, char c)
{
    size_t  env_sz;
    size_t  arg_sz;

    env_sz = count_till_char(org_env, c);
    arg_sz = ft_strlen(arg_rmv);
    if (env_sz == arg_sz)
    {
        if (!ft_strncmp(org_env, arg_rmv, arg_sz))
            return (1);
    }
    return (0);
}

/**
 * This function is a part of biuilt-in UNSET and EXPORT.
 * It creates a new array of strings 'array_new',
 * it copies each string from old array of strings
 * that represents ENV (environmental variable), except of
 * the one string that identical with 'str_to_rmv' up to '='
 * character.
*/
void ft_rmv_arr_str(t_big *big, char *str_to_rmv)
{
    char    **array_new;
    char    **array_old;
    size_t  count;
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    array_old = big->env;
    count = ft_arrlen(array_old);
    // HERE or outside the scope I must check if there is
    // such value to remove it from ENVP.

    // Down some valgrind error.
    array_new = (char **)malloc(sizeof(char *) * (count));
    if (!array_new)
        error_handling(2);
    if (count > 0)
    {
        while (array_old[i] != NULL)
        {   
            if (!same_var(array_old[i], str_to_rmv, '='))
            {
                array_new[j] = ft_strdup(array_old[i]);
                j++;
            }
			i++;
        }
    }
    array_new[j] = NULL;
    big->env = array_new;
    if (array_old)
        ft_free(array_old);
}

/**
 * The function inserts a string 'str_to_add' into a array of strings.
 * It copies all strings from 'array_old' into 'array_new' and inserts
 * the new string. It doesn't free anything. It doesn't re-assign any pointers.
 * All pointers reassigning or freeing must be done outside of its scope.
*/
static char	**ft_add_arr_back(char *str_to_add, char **array_old, char **array_new)
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
    return(array_new);
}

/**
 * The function replace the old value of the environmental
 * variable to the new one.
 */
static void exp_replace_val(t_big *big, char *str_new_val)
{
    char    **old;
    char    **new;
    char    **var_to_rmv;
    
    new = NULL;
    old = NULL;
    var_to_rmv = ft_split(str_new_val, '=');
    ft_rmv_arr_str(big, var_to_rmv[0]);
    ft_free(var_to_rmv);
    old = big->env;
    new = ft_add_arr_back(str_new_val, old, new);
    big->env = new;
    if ((old))
		ft_free(old);
}

/**
 * This function insert a new variable to array of strings 'ENV'.
*/
static void exp_create(t_big *big, char *str_to_add)
{
    char **old;
    char **new;

    new = NULL;
    old = big->env;
    new = ft_add_arr_back(str_to_add, old, new);
    big->env = new;
    if ((old))
		ft_free(old);
}

/**
 * Function check if the variable given by argument is in t_big in envp.
 * It takes characters till '=' sign and compare it to each string in envp,
 * considering characters till '=' sign. In case of succes return 1,
 * other way it returns 0.
*/
static int   exp_check_var(char **env, char *arg)
{
    size_t  env_str;
    size_t  arg_str;
    int     i;

    i = 0;
    arg_str = count_till_char(arg, '=');
    while (env[i])
    {
        env_str = count_till_char(env[i], '=');

        if (arg_str == env_str)
        {
            if (!ft_strncmp(env[i], arg, arg_str))
                return(1);
        }
        i++;
    }
    return(0);
}

// EXIT_STATUS checker. if ANY of the arguments starts with '='
// exit_status is 1.
static void export_exit_status(t_big *big, char **cmd_arg)
{
    int i;

    i = 0;
    while (cmd_arg[i])
    {
        if (*cmd_arg[i] == '=')
        {
            big->exit_code = 1;
            return ;
        }
        i++;
    }
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
int ft_export(t_big *big, t_data *comm_info)
{
    char	**cmd_arg;
    size_t  i;
    size_t  a;

	cmd_arg = comm_info->cmd;
    i = 0;
    a = 1;
    while(cmd_arg[a] != NULL)
    {
        if (ft_strchr(cmd_arg[a], '='))
        {
            if (*cmd_arg[a] == '=')
                ft_printf("-bash: export: `%s': not a valid identifier\n", cmd_arg[a]);
            // 3.A. if any 2 or further string has any character and '=' in the end, 
            // and '=' is only one occurence and it's in the end of the string.
            
            // It check if its variable is in array, if yes - do nothing,
            // if not - it creates a variable with no values.
            else if (!exp_check_var(big->env, cmd_arg[a]))
            {
                // LIBRARY ARRAY OF ARRAYS
                // to make a generalized function to insert a string
                // in the end of array of arrays
                printf("There is no such variable. I run exp_create\n");
                exp_create(big, cmd_arg[a]);
            }
            // 3.C. if 3.B a variable exists and has a value, it replaces an old
            // value to the new one.
            else if (exp_check_var(big->env, cmd_arg[a]))
            {
                printf("Such variable is already in ENVP. exp_replace_val\n");
                exp_replace_val(big, cmd_arg[a]);
            }
        }
        // 2. if string string 2+ == "anything with no '=' at all"
        else if (!ft_strchr(cmd_arg[a], '='))
        {
            printf("I don't see = sign.\n");
            big->exit_code = 0;
        }
        a++;
    }
    export_exit_status(big, cmd_arg);
}
