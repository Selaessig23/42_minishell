/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:30:36 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/19 09:39:18 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the exit of the programm is organised
 */

/**
 * @brief this function exits frees all allocated memory
 * spaces and exits the program
 * 
 * @param big struct with all command infos 
 * that are required for executing (incl. exit code)  
 * that have to be freed
 * @param print_exit if true exit should be printed
 */
void	ft_exit_minishell(t_big *big, bool print_exit)
{
	int	exitcode;

	if (print_exit == true)
		ft_putstr_fd("exit\n", 1);
	exitcode = 0;
	rl_clear_history();
	exitcode = big->exit_code;
	free_t_big(big);
	exit(exitcode);
}
