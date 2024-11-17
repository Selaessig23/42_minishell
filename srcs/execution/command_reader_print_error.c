/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reader_print_error.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:15:16 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 21:51:23 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief helper functin of no_cmd_path
 * st.st_mode & S_IFMT = 
 * This extracts the file type from the st_mode field by masking the mode bits 
 * with S_IFMT, which is the bitmask for the file type
*/
static int	err_handling_executable(char *executable)
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

/**
 * Prints a specific error message to standard error 
 * when a command is not found in the system's executable paths.
 * 
 * for case:
 * 1. ft_check_defaultpath
 * missing.out, "aaa", minishell.h, $, $?, README.md
 * 
 * 2. is_absolute_path
 * /test_files
 *
 * @param cmd_plus_args[0] The first element of **cmd_plus_args 
 * is the command.
 */
static int	no_cmd_path(char **cmd_plus_args, char **binarypaths)
{
		ft_check_defaultpath(cmd_plus_args[0], binarypaths);
		ft_putstr_fd(cmd_plus_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
}

// Check if it's a directory
int is_dir_err_handling(char *cmd)
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

/// valid or not
int is_absolute_path_to_exe_err_handling(char *cmd)
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
		if (!no_cmd_path(cmd_plus_args, binarypaths))
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

/**
 * It explicitly prints an error message 
 * (via "no_cmd_path") if the command cannot be found.
 * 
 * Returns 1 if cmd_plus_args[0] is executable,
 * returns 0 if cmd_plus_args[0] is not executable.
 */
int	is_valid_cmd_and_print_err(char **cmd_plus_args, t_big *big)
{
    if (is_dir_err_handling(cmd_plus_args[0]))
        return(0);
    else if (is_attempt_to_execute(cmd_plus_args[0], "./", 2))
    {
        if (err_handling_executable(cmd_plus_args[0]))
            return (1);
        return (0);
    }
    else if (is_absolute_path(cmd_plus_args[0], "/", 1))
    {
        if (is_absolute_path_to_exe_err_handling(cmd_plus_args[0]))
            return (1);
        else
            return (0);
    }
    if (get_path_from_env_or_binarypaths(big, cmd_plus_args))
        return (1);
    else
        return (0);
}
