/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:50:26 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 15:58:19 by mpeshko          ###   ########.fr       */
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
 * function to print a string, if there the option "-n"
 * was set, then also print a new line afterwards
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
	if (*argv && !(ft_strncmp(*argv, "-n", ft_strlen(*argv))))
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
	// if (fd > 2)
	// 	close(fd);
	big->exit_code = 0;
}
