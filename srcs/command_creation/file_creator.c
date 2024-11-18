/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:26:43 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/18 09:33:58 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * file to check accessibility of files, creates heredocs if asked for and 
 * in case of output redirect also creates the files that are asked for in 
 * command line input
 */

/**
 * @brief function that opens heredoc files if they are accessible
 * and returns the fd
 * 
 * @param filename file to open (in cwd)
 * @param wr if set to true, than open file with aim write,
 * otherwise open with aim read
 */
int	fd_here_creator(char *filename, bool wr)
{
	int		fd;

	fd = 0;
	if (access(filename, F_OK) && wr == true)
	{
		fd = open(filename, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
			error_handling(1);
	}
	else if (!access(filename, F_OK) && wr == true)
	{
		fd = open(filename, O_WRONLY | O_TRUNC);
		if (fd == -1)
			error_handling(1);
	}
	else if (!access(filename, F_OK))
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			error_handling(1);
	}
	return (fd);
}

/**
 * checks if infile is accessible and opens it. Initiate heredoc if required.
 * 
 * @param heredoc to check if a new heredoc file has to be created
 * @param infile the infile name to read from
 */
int	fd_in_checker(t_data *comm_info, char *infile, t_big **p_big)
{
	int		fd_in;

	fd_in = 0;
	if (comm_info->in_heredoc == true)
		fd_in = heredoc_start(comm_info, infile, p_big);
	else if (access(infile, F_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_dprintf("%s: No such file or directory\n", infile);
		fd_in = -1;
	}
	else if (access(infile, R_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(infile, STDERR_FILENO);
		ft_dprintf(": Permission denied\n");
		fd_in = -1;
	}
	else
		fd_in = open(infile, O_RDONLY);
	return (fd_in);
}

/**
 * @brief function to get the fd of the outfile and check 
 * accessibility
 * 
 * @param appender information of filename should be opened with trunc-mode
 * or append-mode (true)
 * @param filename filename (outfile) to write in 
 */
static int	ft_get_fd(bool appender, char *filename)
{
	int	fd_out;

	fd_out = 0;
	if (!access(filename, W_OK) && appender == true)
	{
		fd_out = open(filename, O_WRONLY | O_APPEND);
		if (fd_out == -1)
			error_handling(1);
	}
	else if (!access(filename, W_OK))
	{
		fd_out = open(filename, O_WRONLY | O_TRUNC);
		if (fd_out == -1)
			error_handling(1);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_dprintf("%s: Permission denied\n", filename);
		return (-1);
	}
	return (fd_out);
}

/**
 * function to check if outfile exists. If not it will be created. 
 * If yes, function ft_get_fd will check accessibility
 * 
 * @param appender information of filename should be opened with trunc-mode
 * or append-mode (true)
 * @param filename filename (outfile) to write in 
 */
int	fd_out_creator(bool appender, char *filename)
{
	int		fd_out;

	fd_out = 0;
	if (access(filename, F_OK))
	{
		fd_out = open(filename, O_WRONLY | O_RDONLY | O_CREAT, 0644);
		if (fd_out == -1)
			error_handling(1);
	}
	else
	{
		fd_out = ft_get_fd(appender, filename);
	}
	return (fd_out);
}
