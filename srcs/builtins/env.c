/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:48:48 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/10 20:48:48 by mpeshko          ###   ########.fr       */
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
 * TODO: set exit correct (when 1?) status in struct big after execution
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
	while (env_list && *env_list)
	{
		ft_putstr_fd(*env_list, fd);
		ft_putchar_fd('\n', fd);
		env_list += 1;
	}
	if (fd > 2)
		close(fd);
	big->exit_code = 0;
}
