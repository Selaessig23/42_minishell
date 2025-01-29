/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:59:10 by mpeshko           #+#    #+#             */
/*   Updated: 2025/01/29 16:59:46 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if it is parent type built-ins (executed in parent, not child)
 * Parent type built-ins are built-ins that fully executable
 * only when it is only one command that executes without
 * forking.
 */
int	check_parent_builtin(t_data *comm_info)
{
	char	**argv;

	argv = comm_info->cmd;
	if (argv[0] != NULL)
	{
		if (is_exact_string(argv[0], "cd"))
			return (1);
		if (is_exact_string(argv[0], "export")
			&& ft_arrlen(argv) > 1)
			return (1);
		if (is_exact_string(argv[0], "unset"))
			return (1);
		if (is_exact_string(argv[0], "exit"))
			return (1);
		if (is_exact_string(argv[0], "help"))
			return (1);
	}
	return (0);
}

/**
 * @brief function to check for child type built-in-commands:
 * echo, pwd, env
 *
 * @param comm_info struct with all necessary infos to
 * execute a single command
 */
int	check_child_builtin(t_data *comm_info)
{
	char	**argv;

	argv = comm_info->cmd;
	if (argv[0] != NULL)
	{
		if (is_exact_string(argv[0], "echo"))
			return (1);
		if (is_exact_string(argv[0], "pwd"))
			return (1);
		if (is_exact_string(argv[0], "env"))
			return (1);
		if (is_exact_string(argv[0], "help"))
			return (1);
		if (is_exact_string(argv[0], "export")
			&& ft_arrlen(argv) == 1)
			return (1);
	}
	return (0);
}
