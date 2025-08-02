/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_reset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:11:05 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/19 15:11:12 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief function to reset the global variable
 * g_signalnum (it is only set to !0 if a signal was used)
 * and defines the exit code in case of a signal
 * 
 * @brief big struct with all necessary information to run a command, 
 * exit_codes are saved here
 */
void	signal_set_exitcode_and_reset(t_big *big)
{
	g_signalnum = 0;
	big->exit_code = 130;
}
