/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:16:01 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 20:16:01 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * this function handles errors:
 * it prints error messages from errno
 * and exits the program
 *
 * @param err if param is set, there must be a specific error
 * e.g. 1 = input error
 * @param i the struct which contains all required infos for minishell program
 */
void	error_and_exit(int err)
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
	{
		exit(127);
	}
	else if (err == 4)
		ft_putstr_fd("PATH not readable from ENVP\n", 2);
	ft_putstr_fd("Error occurred! errno:\n", 2);
	ft_putendl_fd(strerror(err), 2);
	exit(EXIT_FAILURE);
}
