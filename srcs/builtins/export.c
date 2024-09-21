#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the inbuilt-function "export"
 * which should work similar to the bash-function
 * of same name is created
 */

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

    // 3.A. if any 2 or further string has any character and '=' in the end, 
    // and '=' is only one and it the end of the string.
    // It check if its variable is in array, if yes - do nothing,
    // if not - it creates a variable with no values. Then check
    // next string(s)...

    // 3.B. if any 2 or further string has any character and '='
    // in the middle. It creates a varible and each character after
    // the first occurence of '=' sign becomes a value for this variable.
    //
    // 3.C. if 3.B a variable exists and has a value, it replaces an old
    // value to the new one.
    //
    // LIBRARY ARRAY OF ARRAYS
    // - a function to insert a string in the end
    // - a function to edit any string in an array of arrays.
    return (0);
}