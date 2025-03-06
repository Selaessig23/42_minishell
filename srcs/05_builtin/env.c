/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:20:14 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/11 17:20:19 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the inbuilt-function "env"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to print all env-variables
 * 
 * fd-handling is done in execution part
 * 	// if (fd > 2)
 * 	// 	close(fd);
 * 
 * @param comm_info struct with all necessary infos to 
 * execute a single command  
 * @param big big struct with all command infos, inclusive
 * env and exit status
 */
void	ft_print_env(t_data *comm_info, t_big *big)
{
	char	**env_list;
	int		fd;

	fd = comm_info->fd_outfile;
	if (!(big->env) || !(*(big->env)))
	{
		big->exit_code = 0;
		return ;
	}
	env_list = big->env;
	while (env_list && *env_list && ft_strchr(*env_list, '='))
	{
		ft_putstr_fd(*env_list, fd);
		ft_putchar_fd('\n', fd);
		env_list += 1;
	}
	big->exit_code = 0;
}
