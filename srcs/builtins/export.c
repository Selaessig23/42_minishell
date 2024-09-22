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
            if (!ft_strncmp(env[i], arg, ft_strlen(arg)))
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
            
            // Чи варто об'єднати 3.A і 3.B. Алгоритми дій доволі схожі.

            // 3.A. if any 2 or further string has any character and '=' in the end, 
            // and '=' is only one occurence and it's in the end of the string.
            
            // It check if its variable is in array, if yes - do nothing,
            // if not - it creates a variable with no values. Then check
            // next string(s)...
            else if (!exp_check_var(big->env ,cmd_arg[a]))
            {
                // LIBRARY ARRAY OF ARRAYS
                // - a function to insert a string in the end of arraz of arrays
                //exp_create();
                printf("There is no such variable\n");
            }
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

            // 3.C. if 3.B a variable exists and has a value, it replaces an old
            // value to the new one.
  
        }
        // 2. if string string 2+ == "anything with no '=' at all"
        // 3. if string 1 == export and string 2 == "anything with no '=' and
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