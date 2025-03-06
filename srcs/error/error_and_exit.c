/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:16:01 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 20:16:01 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * the following 2 functions print errors in case of 
 * problems within the program
 */
void	ft_print_error_messages_2(int err)
{
	ft_putstr_fd("Error occurred!\n", 2);
	if (errno != 0)
	{
		ft_putstr_fd("errno: \n", 2);
		ft_putendl_fd(strerror(err), 2);
	}
}

void	ft_print_error_messages_1(int err)
{
	if (err == 1)
	{
		errno = 5;
		ft_putstr_fd(INPUT_ERROR, 2);
	}
	else if (err == 2)
	{
		errno = 12;
		ft_putstr_fd("Problems with malloc\n", 2);
		exit (1);
	}
	else if (err == 3)
		exit(127);
	else if (err == 4)
		ft_putstr_fd("PATH not readable from ENVP\n", 2);
	else if (err == 5)
		ft_putstr_fd("Unable to start minishell without envp.\n", 2);
	else if (err != 0)
		ft_print_error_messages_2(err);
}

/**
 * this function organises error handling:
 * it prints error messages from errno,
 * frees allocated memory if required and
 * and exits the program
 *
 * @param err if param is set, there must be a specific error
 * e.g. 1 = input error
 * @param i the struct which contains all required infos for minishell program
 */
void	error_and_exit(int err, t_big *big)
{
	if (big)
		free_t_big(big);
	ft_print_error_messages_1(err);
	exit(EXIT_FAILURE);
}
