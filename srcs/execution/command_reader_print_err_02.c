/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reader_print_err_02.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:56:16 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 22:07:54 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints a specific error message to standard error 
 * when a command is not found in the system's executable paths.
 * 
 * for case:
 * cattt, missing.out, "aaa", minishell.h, $, $?, README.md
 *
 * @param cmd_plus_args[0] The first element of **cmd_plus_args 
 * is the command.
 */
static int	no_path_in_env_check_binarypaths(char *cmd, char **binarypaths)
{
		ft_check_defaultpath(cmd, binarypaths);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
}

int	get_path_from_env_or_binarypaths(t_big *big, char **cmd_plus_args)
{
	char	*cmd_path;
	char	**binarypaths;
	char	**c_env;

	binarypaths = big->binarypaths;
	c_env = big->env;
	cmd_path = get_path(cmd_plus_args[0], c_env);
	if (!cmd_path)
	{
		if (!no_path_in_env_check_binarypaths(cmd_plus_args[0], binarypaths))
			return (0);
		else
			return (1);
	}
	else
	{
		free(cmd_path);
		return (1);
	}
}

/// valid or not
int	is_absolute_path_to_exe_err_handling(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
        return (1);
    else
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd, STDERR_FILENO);
        ft_putstr_fd(": No such file or directory", STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        return (0);
    }
}

/**
 * @brief helper functin of no_cmd_path
 * st.st_mode & S_IFMT = 
 * This extracts the file type from the st_mode field by masking the mode bits 
 * with S_IFMT, which is the bitmask for the file type
*/
int	err_handling_executable(char *executable)
{
	if (access(executable, F_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(executable, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (0);
	}
	else if (access(executable, R_OK) || access(executable, X_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(executable, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

// Check if it's a directory
int	is_dir_err_handling(char *cmd)
{
	struct stat	check_dir;

	if (stat((cmd), &check_dir) == 0 && S_ISDIR(check_dir.st_mode))
	{
		if ((!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1) 
            || (is_last_char(cmd, '/'))) && S_ISDIR(check_dir.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			return (1);
		}
	}
    return (0);
}
