/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_error_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:27:35 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 23:15:51 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is a wrapper around the dup2 system call.
 * It attempts to duplicate dupfd onto newfd. If dup2 fails, it handles
 * the error by closing the file descriptors,
 * printing an error message, and terminating the program.
 */
void	w_dup2(int dupfd, int newfd)
{
	if (dup2(dupfd, newfd) == -1)
	{
		perror("dup2");
		if (newfd > 2)
			close(newfd);
		if (dupfd > 2)
			close(dupfd);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief This function handles errors related to pipe creation.
 * It closes the provided file descriptor open_fd, prints an error message
 * related to pipe, and exits the program.
 */
void	w_errpipe_close(int open_fd)
{
	if (open_fd > 2)
		close(open_fd);
	perror("pipe");
	exit(EXIT_FAILURE);
}

/**
 * @brief This function handles errors during a fork operation.
 * When fork fails, it prints an error message, closes the file descriptor
 * "open_fd", closes both ends of a pipe (given by pipe_fd), and exits
 * the program.
 */
void	w_errfork_close(int open_fd, int *pipe_fd)
{
	perror("Fork Error");
	if (open_fd > 2)
		close(open_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(EXIT_FAILURE);
}

void	close_fd_with_error_handling(void)
{
	perror("Error closing file descriptor");
	exit(EXIT_FAILURE);
}
