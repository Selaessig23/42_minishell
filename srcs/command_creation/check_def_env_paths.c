/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_def_env_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:27:57 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/13 15:28:00 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * file to organise the check of the default env-paths-value
 * (in case of the value of env-variable "PATH" was changed
 * by builtin-function "export")
 */

/**
 * @brief function to count the amount of paths in which the 
 * source file binary is part of
 * 
 * @param binary the source file to search for
 * @param arr_binarypaths the array of path to search in
 */
size_t	ft_match_counter(char *binary, char **arr_binarypaths)
{
	size_t	i;
	size_t	counter;
	char	*path;

	i = 0;
	counter = 0;
	while (arr_binarypaths[i])
	{
		path = build_cmd_path(arr_binarypaths[i], binary);
		if (access(path, F_OK | X_OK) == 0)
			counter += 1;
		free(path);
		i += 1;
	}
	return (counter);
}

/**
 * @brief function to fill the pointer of path_matches 
 * with all paths where source file is part of
 * 
 * @param path_matches a pointer to an array of paths which consists 
 * of all paths that have the source file inside
 * @param binary the source file to search for
 * @param arr_binarypaths the array of path to search in
 */
void	ft_match_filler(char ***p_path_matches, char *bin, char **arr_binpaths)
{
	size_t	i;
	size_t	counter;
	char	**path_matches;
	char	*path;

	i = 0;
	counter = 0;
	path_matches = *p_path_matches;
	while (arr_binpaths[i])
	{
		path = build_cmd_path(arr_binpaths[i], bin);
		if (access(path, F_OK | X_OK) == 0)
		{
			path_matches[counter] = ft_strdup(arr_binpaths[i]);
			counter += 1;
		}
		free(path);
		i += 1;
	}
	path_matches[counter] = NULL;
}

/**
 * @brief function to print error message in case of binary file command is 
 * found in some of the binary paths
 * 
 * @param binary the binary command file
 * @param pathmatches the paths where binary is part of
 */
void	ft_print_error(size_t match_counter, char *binary, char **path_matches)
{
	int	i;

	i = 0;
	ft_printf("Command \'%s\' is available in the following places\n", binary);
	while (match_counter > 0)
	{
		ft_putstr_fd(" * ", 2);
		ft_putstr_fd(path_matches[match_counter -1], 2);
		ft_putchar_fd('/', 2);
		ft_putendl_fd(binary, 2);
		i += 1;
		match_counter -= 1;
	}
	ft_putstr_fd("The command could not be located because '", 2);
	while (i > 0)
	{
		ft_putstr_fd(path_matches[i - 1], 2);
		i -= 1;
		if (i > 0)
			ft_putchar_fd(':', 2);
	}
	ft_putendl_fd("/' is not included in the PATH environment variable.", 2);
}

/**
 * @brief function that checks if the binary is found in the 
 * default folders of variable path of env (if, for example,
 * the env->path was changed by using export function)
 * 
 * @param binary the binary command to search for
 * @param binarypaths a copy of default value of PATH (part of env)
*/
void	ft_check_defaultpath(char *binary, char **binarypaths)
{
	char	**path_matches;
	size_t	match_counter;

	match_counter = ft_match_counter(binary, binarypaths);
	path_matches = NULL;
	if (match_counter == 0)
		return ;
	path_matches = ft_calloc((match_counter + 1), sizeof(char *));
	if (!path_matches)
		error_handling(1);
	ft_match_filler(&path_matches, binary, binarypaths);
	ft_print_error(match_counter, binary, path_matches);
	ft_free(path_matches);
}
