/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:50:26 by mstracke          #+#    #+#             */
/*   Updated: 2025/01/16 15:12:01 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the inbuilt-function "echo"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief check for request to not output a new line 
 * 
 * @param option the second string of the argv-command package,
 * if it is equal to -n | -nnnnnnnnnnnnnnnnn.., the option
 * "not output a new line" was set
 * 
 * @return returns 1 if true (request) or 0 if not
 */
static int	ft_nl_check(char *option)
{
	if (*option && *(option + 1) 
		&& !(ft_strncmp(option, "-n", ft_strlen(option))) 
		&& is_exact_string("-n", option))
		return (1);
	else if (*option && *(option + 1) 
		&& *option == '-' && *(option + 1) == 'n')
	{
		option += 1;
		while (*option)
		{
			if (*option != 'n')
				return (0);
			option += 1;
		}
		return (1);
	}
	return (0);
}

/**
 * function to print a string. if the option "-n"
 * was set, then also print a new line afterwards
 * 
 * fd-handling is done in execution part
 * 	// if (fd > 2)
 * 	// 	close(fd);
 * to only check for -n (not -nnnnnnnnnnnnn..)
 * // if (*argv && !(ft_strncmp(*argv, "-n", ft_strlen(*argv))))
 *
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 * @param big big struct with all command infos, inclusive
 * env and exit status
 */
void	ft_echo(t_data *comm_info, t_big *big)
{
	char	**argv;
	int		fd;
	bool	no_nl;

	argv = comm_info->cmd;
	no_nl = 0;
	fd = comm_info->fd_outfile;
	argv += 1;
	if (ft_nl_check(*argv))
	{
		no_nl = true;
		argv += 1;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, fd);
		argv += 1;
		if (*argv)
			ft_putchar_fd(' ', fd);
	}
	if (no_nl == 0)
		ft_putchar_fd('\n', fd);
	big->exit_code = 0;
}
