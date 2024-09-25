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
 * This function is a part of biuilt-in UNSET.
 * It creates a new array of strings 'array_new',
 * it copies each string from old array of strings
 * that represents ENV (environmental variable), except
 * the one string that identical with 'str_to_rmv' up to '='
 * character.
*/
static void ft_rmv_arr_str(t_big *big, char *str_to_rmv)
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
    printf("count array_old: %ld\n", count);
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
 * Function check if the variable given by argument is in t_big in envp.
*/
static int   uns_check_var(char **env, char *arg)
{
    size_t  env_str;
    size_t  arg_str;
    int     i;

    i = 0;
    arg_str = ft_strlen(arg);
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

/**
 * @brief function to execute the builtin function "unset"
 * 
 * @param big big big struct with all command infos 
 * that are required for executing builtins or 
 * that have to be freed
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
int ft_unset(t_big *big, t_data *comm_info)
{
    char	**cmd_arg;
    size_t  i;
    size_t  a;

	cmd_arg = comm_info->cmd;
    i = 0;
    a = 1;
    while (cmd_arg[a] != NULL)
    {
        if (uns_check_var(big->env, cmd_arg[a]))
        {
            printf("Such variable is already in ENVP. I remove it.\n");
            ft_rmv_arr_str(big, cmd_arg[a]);
        }
        printf("No %s variable in ENVP.\n", cmd_arg[a]);
        a++;
    }
    return (0);
}

 // EXIT_STATUS checker. if ANY of the arguments starts with '='
// exit_status is 1.