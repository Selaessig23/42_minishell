/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:05:26 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/21 15:05:40 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRPIPTION:
 * file to organise the error messages of builtin cd
 */

/**
 * @brief function checks if there are mor than one argument 
 * or less than one for builtin cd. If YES than error message
 * 
 * @param argv the array of commands (cmd) that holds all information
 * for execution (argv[0] == cd, argv[1] == directory to change to)
 */
static int	cd_no_arg(char **argv)
{
	if (ft_arrlen(argv) < 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd("Please specifiy the path you want to change to\n", 2);
		return (1);
	}
	else if (ft_arrlen(argv) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

/**
 * @brief function to check the accessibility of the file
 * in case of problems with the file it returns an error message
 * 
 * @param argv the array of commands (cmd) that holds all information
 * for execution (argv[0] == cd, argv[1] == directory to change to)
 */
int	cd_error_check(char **argv)
{
	struct stat	check_dir;

	if (cd_no_arg(argv))
		return (1);
	else if (stat((argv[1]), &check_dir) == 0 && !S_ISDIR(check_dir.st_mode))
	{
		ft_dprintf("minishell: cd: %s: Not a directory\n", argv[1]);
		return (1);
	}
	else if (access(argv[1], F_OK))
	{
		ft_dprintf("minishell: cd: %s: No such file or directory\n", argv[1]);
		return (1);
	}
	else if (access(argv[1], X_OK))
	{
		ft_dprintf("minishell: cd: %s: Permission denied\n", argv[1]);
		return (1);
	}
	else
		return (0);
}
