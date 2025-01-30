/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binary_child_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:28:11 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 15:59:21 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file 
 */

/**
 * @brief Checks if a command exists in the provided folders and 
 * returns its path.
 * 
 * @param folders An array with all folder of env var 'PATH'.
 * @param cmd_name The name of the command to check.
 * @return The path to the executable if found, or NULL if not.
 */
char	*exe_exists(char **folders, char *cmd_name)
{
	char	*path;
	int		i;

	i = 0;
	while (folders[i] != NULL)
	{
		path = build_cmd_path(folders[i], cmd_name);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Retrieves all directories listed in the 'PATH' environment variable.
 * It searches for the var name env_var_path in env and returns the content of this var
 * (everything that follows '='), found in env, or NULL if not found
 * 
 * @param env_var_path The name of the environment variable (e.g., "PATH").
 * @param env The environment variables array.
 * @return A pointer to the first folder in the PATH or NULL if not found.
 */
char	*get_all_folders(const char *env_var_path, char **env)
{
	size_t	i;
	size_t	len;
	char	*current_env_var;

	i = 0;
	while (env[i])
	{
		len = 0;
		while (env[i][len] && env[i][len] != '=')
			len++;
		current_env_var = ft_substr(env[i], 0, len);
		if (!current_env_var)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(current_env_var, env_var_path) == 0)
		{
			free(current_env_var);
			return (env[i] + len + 1);
		}
		free(current_env_var);
		i++;
	}
	return (NULL);
}

/**
 * @brief Obtains the path of a (binary) command by 
 * 1st searching the content of 'PATH' environment variable 
 * (= get all folders)
 * 2nd checking in which diretory listed in PATH the binary is located
 * (= exe_exists)
 * 
 * @param cmd_name The name of the command to locate.
 * @param env The environment variables array.
 * @return The command path if found, or NULL if not.
 */
char	*get_path(char *cmd_name, char **env)
{
	char	**folders;
	char	*path;
	char	*all_folders;

	all_folders = get_all_folders("PATH", env);
	if (!all_folders)
		return (NULL);
	folders = ft_split(all_folders, ':');
	if (!folders)
	{
		perror("malloc");
		return (NULL);
	}
	path = exe_exists(folders, cmd_name);
	if (!path)
	{
		ft_freestr(folders);
		return (NULL);
	}
	else
	{
		ft_freestr(folders);
		return (path);
	}
}

/**
 * @brief this function checks if a binary file of the command exists
 * in the paths listed in the env var PATH
 * if YES, it executes th command, if not, it returns error code 127
 */
int	get_path_from_env_path_and_exe(char **cmd_plus_args, char *env[])
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = get_path(cmd_plus_args[0], env);
	if (!cmd_path)
		return (127);
	if (execve(cmd_path, cmd_plus_args, env) == -1)
	{
		free(cmd_path);
		if (errno == ENOENT)
		{
			return (127);
		}
		if (errno == EACCES)
		{
			return (126);
		}
		else
			return (EXIT_FAILURE);
	}
	return (0);
}
