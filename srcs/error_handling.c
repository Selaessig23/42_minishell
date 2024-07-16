/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:53:25 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/16 10:08:51 by mstracke         ###   ########.fr       */
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
void	error_handling(int err)
{
	if (err == 4)
		ft_putstr_fd("PATH not readible from ENVP", 1);
	else if (err == 1)
	{
		errno = 5;
		ft_putstr_fd(INPUT_ERROR, 1);
	}
	else if (err == 2)
	{
		errno = 12;
		ft_putstr_fd("Problems with malloc", 1);
	}
	else if (err == 3)
	{
		ft_putstr_fd("zsh: ", 2);
//		ft_printf("command not found: %s\n", i->commands[com_no][0]);
//		free_struct(i);
		exit(127);
	}
	perror("Error");
	exit(EXIT_FAILURE);
}

