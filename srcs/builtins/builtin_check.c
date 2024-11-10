/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:16:51 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/10 19:36:43 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if it is parent type built-ins
 * Parent type built-ins are built-ins that fully executable
 * only when it is only one command that executes without
 * forking.
 */
int	check_builtin_parent(t_data *comm_info)
{
	char	**argv;

	argv = comm_info->cmd;
	if (argv[0] != NULL)
	{
		if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("cd"))
			return (1);
		if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("export"))
			return (1);
		if (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("unset"))
			return (1);
		if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("exit"))
			return (1);
		if (!ft_strncmp(argv[0], "help", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("help"))
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
int	check_builtin_other(t_data *comm_info)
{
	char	**argv;

	argv = comm_info->cmd;
	if (argv[0] != NULL)
	{
		if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("echo"))
			return (1);
		if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("pwd"))
			return (1);
		if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("env"))
			return (1);
		if (!ft_strncmp(argv[0], "help", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("help"))
			return (1);
	}
	return (0);
}
