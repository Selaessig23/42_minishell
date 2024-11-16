/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_error_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:27:35 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/16 07:31:39 by mpeshko          ###   ########.fr       */
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
		print_stderr("dup2");
		if (newfd > 2)
			close(newfd);
		if (dupfd > 2)
			close(dupfd);
		exit(EXIT_FAILURE);
	}
}

/**
 * Prints a message to standard error describing the error associated
 * with the given argument, based on the current value of errno.
 *
 * The perror() function prints a message to stderr that describes
 * the last error that occurred based on the global variable errno.
 */
void	print_stderr(char *what_error)
{
	perror(what_error);
}

/**
 * Prints an error message based on errno and then exits the program
 * with failure, closing the pipe file descriptors if provided.
 *
 * Uses perror to print a system error message related to the
 * last error (stored in errno), along with the custom message.
 */
void	perror_and_exit(char *what_error, int *pipe_fd)
{
	perror(what_error);
	if (pipe_fd)
	{
		if (close(pipe_fd[0]) == -1)
			perror("Error closing pipe [0]");
		if (close(pipe_fd[1]) == -1)
			perror("Error closing pipe [1]");
	}
	exit(EXIT_FAILURE);
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
	perror_and_exit("pipe", NULL);
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

void	close_fd_with_error_handling()
{
    perror("Error closing file descriptor");
    exit(EXIT_FAILURE);
}
