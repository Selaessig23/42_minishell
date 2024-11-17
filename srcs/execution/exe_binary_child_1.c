/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binary_child_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:28:11 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 23:07:01 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a command exists in the provided folders and 
 * returns its path.
 * 
 * @param folders An array of folder paths.
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
 * @brief Retrieves the folders from the 'PATH' environment variable.
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
 * @brief Obtains the path of a command by searching the 'PATH' 
 * environment variable.
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

int	get_path_from_env_path_and_exe(char **cmd_plus_args, char *env[])
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = get_path(cmd_plus_args[0], env);
	if (!cmd_path)
		return (127);
	execve(cmd_path, cmd_plus_args, env);
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
