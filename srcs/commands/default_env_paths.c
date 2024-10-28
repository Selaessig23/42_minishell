#include "minishell.h"
#include <sys/stat.h>

/**
 * DESCRIPTION:
 * file to organise the check of the default env-paths-value
 */


/**
 * @brief function to count the amount of paths in which the source file binary is part of
 * 
 * @param binary the source file to search for
 * @param arr_binarypaths the array of path to search in
 */
size_t  ft_match_counter(char *binary, char **arr_binarypaths)
{
    size_t  i;
    size_t  counter;

    i = 0;
    counter = 0;
    while (arr_binarypaths[i])
	{
		if (!ft_strncmp(binary, arr_binarypaths[i], ft_strlen(binary))
			&& ft_strlen(binary) == ft_strlen(arr_binarypaths[i]))
            counter += 1;
        i += 1;
    }
    return (counter);
}

/**
 * @brief function to fill the pointer of path_matches with all paths where source file is part of
 * 
 * @param path_matches a pointer to an array of paths which consists of all paths that have the source file inside
 * @param binary the source file to search for
 * @param arr_binarypaths the array of path to search in
 */
void  ft_match_filler(char ***p_path_matches, char *binary, char **arr_binarypaths)
{
    size_t  i;
    size_t  counter;
    char    **path_matches;

    i = 0;
    counter = 0;
    path_matches = *p_path_matches;
    while (arr_binarypaths[i])
	{
		if (!ft_strncmp(binary, arr_binarypaths[i], ft_strlen(binary))
			&& ft_strlen(binary) == ft_strlen(arr_binarypaths[i]))
            path_matches[counter] = ft_strdup(arr_binarypaths[i]);
            counter += 1;
        i += 1;
    }
    path_matches[counter] = NULL;
}

/**
 * @brief function that checks if the binary is found in the 
 * default folders of variable path of env (if, for example,
 * the env->path was changed by using export function)
 * 
 * @param binary the binary command to search for
 * @param binarypaths a copy of default value of PATH (part of env)
*/
int	ft_check_defaultpath(char *binary, char **binarypaths)
{
	char    **path_matches;
    size_t  match_counter;
    int     i;

    i = 0;
    match_counter = ft_match_counter(binary, binarypaths);
    if (match_counter == 0)
        return (0);
    path_matches = ft_calloc(match_counter, sizeof(char *));
    if (!path_matches)
        error_handling(1);
    ft_match_filler(&path_matches, binary, binarypaths);
    ft_printf("Command \'%s\' is available in the following places\n * %s\n", binary, binarypaths);
	while (path_matches[i])
    {
        ft_putstr_fd(path_matches[i], 2);
	    ft_putstr_fd("\n", 2);
        i += 1;
    }
    
	// ft_check_defaultpath(binary, *arr_binarypaths)
	while (arr_binarypaths)
	{
		if (!ft_strncmp(binary, *arr_binarypaths, ft_strlen(binary))
            && ft_strlen(binary) == ft_strlen(*arr_binarypaths))
        {
            ft_putstr_fd(" * ", 2);
            ft_putstr_fd(*arr_binarypaths, 2);
        }
        else
            arr_binarypaths += 1;
    }
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("The command could not be located because '/usr/bin:/bin' is not included in the PATH environment variable.\n", 2);
}
		else
			arr_binarypaths += 1;
	}
	// Freud'scher Versprecher
}
