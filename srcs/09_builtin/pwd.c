/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:13:29 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/18 20:14:08 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION: 
 * in this file the inbuilt-function "pwd"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to get and print current working directory
 * to fd
 * 
 * @param fd the file descriptor to write in
 */
static void	ft_get_env_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		error_and_exit(2);
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
}

/**
 * @brief function to print content of env-variable 'pwd' to
 * big->fd_outfile (int). If there are no permissions rights,
 * big->fd_outfile will be < 0.
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env and exit status
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
void	ft_print_pwd(t_big *big, t_data *comm_info)
{
	int	fd;

	fd = comm_info->fd_outfile;
	if (fd >= 0)
		ft_get_env_pwd(fd);
	big->exit_code = 0;
}
