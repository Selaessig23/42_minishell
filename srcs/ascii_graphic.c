/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_graphic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:28:16 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 14:28:19 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_welcome_help(int fd)
{
	ft_putstr_fd("MINISHELL, version 9.9.9.9.0\n", fd);
	ft_putstr_fd("\xC2\xA9 by Maryna Peshko and Markus Stracke\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
	ft_putstr_fd("This shell is written in accordance ", fd);
	ft_putstr_fd("with 42-subject \"minishell\"\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
	ft_putstr_fd("General instructions:\n", fd);
	ft_putstr_fd("The following operators are not ", fd);
	ft_putstr_fd("considered (=non-functional):\n", fd);
	ft_putstr_fd("||\n", fd);
	ft_putstr_fd("&&\n", fd);
	ft_putstr_fd("[]\n", fd);
	ft_putstr_fd("{}\n", fd);
	ft_putstr_fd("The shell will not use wildcards.\n", fd);
	ft_putstr_fd("It only considers the following ", fd);
	ft_putstr_fd("redirctions: <, >, <<, >>\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
}

void	ft_welcome(void)
{
	int	fd;

	fd = 1;
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("            _         _       _            _  _\n", fd);
	ft_putstr_fd("	   (_)       (_)     | |          | || |\n", fd);
	ft_putstr_fd("_ __ ___    _  _ __   _  ___ | |__    ___ | || |\n", fd);
	ft_putstr_fd("| '_ ` _ \\ | || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n", fd);
	ft_putstr_fd("| | | | | || || | | || |\\__ \\| | | ||  __/| || |\n", fd);
	ft_putstr_fd("|_| |_| |_||_||_| |_||_||___/|_| |_| \\___||_||_|\n", fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("\n", fd);
	ft_welcome_help(fd);
	ft_putstr_fd("HAVE FUN USING IT!!!\n\n", fd);
}
