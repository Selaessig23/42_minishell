/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reader_print_err_01.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:55:51 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 23:08:08 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (0);
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
