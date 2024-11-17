/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binary_child_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 23:14:39 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 23:14:39 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execve_no_free(char *cmd, char **cmd_plus_args, char *env[])
{
	execve(cmd, cmd_plus_args, env);
	{
		if (errno == ENOENT)
			return (127);
		else if (errno == EACCES)
			return (126);
		else
			return (EXIT_FAILURE);
	}
}

/**
 * This function checks if a given command cmd refers to a valid directory.
 * 
 * 1. Calls stat: It retrieves the file status of cmd and stores it 
 * in a struct stat variable (check_dir).
 * 2. Checks Path Prefix and Directory Type. If cmd starts with ./, /, or 
 * ends with /, and the path corresponds to a directory 
 * (S_ISDIR evaluates to true), it returns 0.
 */
static int	is_command_directory(char *cmd)
{
	struct stat	check_dir;

	if (stat((cmd), &check_dir) == 0)
	{
		if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1) 
				|| (is_last_char(cmd, '/'))) && S_ISDIR(check_dir.st_mode))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

static int	is_just_name_of_directory(const char *cmd_is_name_of_directory)
{
	struct stat	check_dir;

	if (stat((cmd_is_name_of_directory), &check_dir) == 0)
	{
		if (S_ISDIR(check_dir.st_mode))
		{
			return (1);
		}
		return (0);
	}
	return (0);
}

/**
 * Check if the file exists and is executable an
 * if it is an absolute path, return 1.
 */
static int	is_absolute_path_to_exe(const char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
	{
		if (is_absolute_path(cmd, "/", 1))
		{
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

/**
 * @brief Executes a command with its arguments, searching for 
 * the executable path.
 * Return value is an exit code of a child process.
 * 
 * @param argument The command and its arguments as a string.
 * @param env The environment variables array.
 */
int	exe_child_binary(char **cmd_plus_args, char *env[])
{
	if (!is_minishell_command(cmd_plus_args[0], env))
		return (0);
	else if (is_command_directory(cmd_plus_args[0]))
		return (ft_execve_no_free(cmd_plus_args[0], cmd_plus_args, env));
	else if (is_attempt_to_execute(cmd_plus_args[0], "./", 2))
		return (ft_execve_no_free(cmd_plus_args[0], cmd_plus_args, env));
	else if (is_absolute_path_to_exe(cmd_plus_args[0]))
		return (ft_execve_no_free(cmd_plus_args[0], cmd_plus_args, env));
	else if (is_just_name_of_directory(cmd_plus_args[0]))
		return (127);
	else
		return (get_path_from_env_path_and_exe(cmd_plus_args, env));
}
