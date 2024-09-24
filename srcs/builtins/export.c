#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the inbuilt-function "export"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to insert a string into the given array
 * of strings.
 * 
 * @param 
 * @param 
 */
/*void	ft_add_arr_back_cpy(char *str_to_add, t_big *big)
{
	//t_data	*comm_info;
	char	**array_old;
	char	**array_new;
	size_t	count;
	size_t	i;

	i = 0;
	//comm_info = *p_comm_info;
	array_old = big->env;
	count = ft_arrlen(array_old);
	// printf("what the hack A, count:: %zu\n", count);
	array_new = (char **)malloc(sizeof(char *) * (count + 2));
	if (!array_new)
		error_handling(2);
	if (count > 0)
	{
		// printf("what the hack A-a, count\n");
		while (array_old[i] != NULL)
		{
			// printf("what the hack A-b, count\n");
			array_new[i] = ft_strdup(array_old[i]);
			i++;
		}
	}
	// printf("what the hack A-c, count\n");
	array_new[i] = ft_strdup(str_to_add);
	// printf("what the hack A-d, count\n");
	if (!array_new[i])
		error_handling(2);
	i += 1;
	array_new[i] = NULL;
	big->env = array_new;
	// printf("what the hack B: %s\n", *p_command_array[0]);;
	// printf("what the hack B: %s\n", comm_info->cmd[0]);;
	if ((array_old))
		ft_free(array_old);
}*/

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
 * This function insert a new variable to array of strings 'ENV'.
*/
static void exp_create(t_big *big, char *str_to_add)
{
    char **old;
    char **new;

    new = NULL;
    old = big->env;
    //ft_add_arr_back_cpy(str_to_add, big);
    new = ft_add_arr_back(str_to_add, old, new);
    big->env = new;
    if ((old))
		ft_free(old);
}

/**
 * This function counts a number of characters in a given string
 * up to the given character 'up_to'
*/
size_t  count_till_char(char *str, char up_to)
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
 * Function check if the variable given by argument is in t_big in envp.
 * It takes characters till '=' sign and compare it to each string in envp,
 * considering characters till '=' sign. In case of succes return 1,
 * other way it returns 0.
*/
int   exp_check_var(char **env, char *arg)
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
    while (cmd_arg[i] != NULL)
    {
        printf("cmd_arg[%li]: %s\n", i, cmd_arg[i]);
        i++;
    }
    
    // check all strings after 1st string "export"
    while(cmd_arg[a] != NULL)
    {
        if (ft_strchr(cmd_arg[a], '='))
        {
            // do something
            // 2.A. If string 1 == export and string 2 == the first character is '='
            // then display  message -bash: export: `==': not a valid identifier
            // and exit_code is - one (checker functon after the loop)
            if (*cmd_arg[a] == '=')
                ft_printf("-bash: export: `%s': not a valid identifier\n", cmd_arg[a]);
            
            // 3.A. if any 2 or further string has any character and '=' in the end, 
            // and '=' is only one occurence and it's in the end of the string.
            
            // It check if its variable is in array, if yes - do nothing,
            // if not - it creates a variable with no values.
            else if (!exp_check_var(big->env ,cmd_arg[a]))
            {
                // LIBRARY ARRAY OF ARRAYS
                // to make a generalized function to insert a string
                // in the end of array of arrays
                printf("There is no such variable. I run exp_create\n");
                exp_create(big, cmd_arg[a]);
            }
            // 3.C. if 3.B a variable exists and has a value, it replaces an old
            // value to the new one.
            else if (exp_check_var(big->env ,cmd_arg[a]))
            {
                // LIBRARY ARRAY OF ARRAYS
                // - a function to edit any string in an array of arrays.
                // exp_replace_val();
                printf("Such variable is already in ENVP\n");
            }
            // 3.B. if any 2 or further string has any character and '='
            // in the middle. It check if its variable is in array,
            // creates a varible and each character after
            // the first occurence of '=' sign becomes a value for this variable.
        }
        // 2. if string string 2+ == "anything with no '=' at all"
        else if (!ft_strchr(cmd_arg[a], '='))
        {
            printf("I don't see = sign\n");
            big->exit_code = 0;
        }
        a++;
        
    }
    // EXIT_STATUS checker. if ANY of the arguments starts with '='
    // exit_status is 1.
    /*
    while
    if (*cmd_arg[a] == '=')
            {
                printf("exit code: %i\n", big->exit_code);
                ft_printf("-bash: export: `%s': not a valid identifier\n", cmd_arg[a]);
                big->exit_code = 1;
                printf("exit code: %i\n", big->exit_code);
    */

    //
    // LIBRARY ARRAY OF ARRAYS
    // - a function to insert a string in the end of arraz of arrays
    // - a function to edit any string in an array of arrays.
    return (0);
}