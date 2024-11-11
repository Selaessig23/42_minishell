
#include "minishell.h"

/**
 * @brief Used to discard input when no valid command is provided,
 * preventing unnecessary input processing from the original file descriptor.
 *
 * The "dev_null" function is used when the command in "acces_cmd" function
 * is invalid.
 *
 * In case of an issue with the command, the program redirects the
 * input source (fd_to_read) to /dev/null. So there's no input to process,
 * and it discards anything that might have been read from the original
 * file descriptor.
 */
int	dev_null(int read_from)
{
	if (read_from > 0)
		close(read_from);
	read_from = open("/dev/null", O_RDONLY);
	return (read_from);
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
 * @brief This function is a wrapper around the dup2 system call.
 * It attempts to duplicate dupfd onto newfd. If dup2 fails, it handles
 * the error by closing the fd_open file descriptor (if it's not -2),
 * printing an error message, and terminating the program.
 * The function ensures that the original file descriptor (dupfd) is
 * closed whether the operation succeeds or fails.
 *
 * @param dupfd: The file descriptor to duplicate.
 * @param newfd: The target file descriptor where dupfd will be duplicated.
 * @param fd_open: An additional file descriptor that will be closed on error,
 * unless its value is -2, which means it will be skipped.
 */
void	w_dup2(int dupfd, int newfd, int fd_open)
{
	if (dup2(dupfd, newfd) == -1)
	{
		if (fd_open != -2)
			close(fd_open);
		print_stderr("dup2");
		close(dupfd);
		exit(EXIT_FAILURE);
	}
	else
		close(dupfd);
}

/**
 * @brief This function handles errors related to pipe creation.
 * It closes the provided file descriptor open_fd, prints an error message
 * related to pipe, and exits the program.
 */
void	w_errpipe_close(int open_fd)
{
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
	close(open_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(EXIT_FAILURE);
}

static int	child(t_data *comm_info, t_data *c_i_next, t_big *big, int *fd)
{
	ft_handle_signals_childs();
	close(fd[0]);

	//ft_dprintf("pipes fd[0] (%d) is closed in CHILD\n", fd[0]);

	if (c_i_next == NULL)
	{
		// fprintf(stderr, "child. it's the last command\n");
		if (comm_info->fd_infile == 0 && comm_info->fd_outfile == 1)
		{
			// fprintf(stderr, "no < or << and > or >>\n");
			if (check_builtin_other(comm_info))
			{
				exe_other_builtin(comm_info, big);
				exit(EXIT_SUCCESS);
			}
			else
				call_cmd(comm_info->cmd, big->env);
		}

		//////// ????
		if (comm_info->fd_outfile > 1)
		{
			//ft_dprintf("output to file\n");
			dup2(comm_info->fd_outfile, STDOUT_FILENO);
			ft_dprintf("comm_info->fd_outfile (%d) is closed IN CHILD\n", comm_info->fd_outfile);
			close(comm_info->fd_outfile);
		}
		if (comm_info->fd_infile > 0)
		{
			// fprintf(stderr, "input from file or prev. pipe\n");
			// printf("fd_infile X: %i\n", comm_info->fd_infile);
			dup2(comm_info->fd_infile, STDIN_FILENO);
			// printf("fd after dup: %i\n", STDIN_FILENO);
			close(comm_info->fd_infile);
		}
		close(fd[1]);
	}
	else if (c_i_next != NULL)
	{
		if (comm_info->fd_infile > 0)
		{
			dup2(comm_info->fd_infile, STDIN_FILENO);
			ft_dprintf("comm_info->fd_infile (%d) is closed IN CHILD\n", comm_info->fd_infile);
			close(comm_info->fd_infile);
		}
		if (comm_info->fd_outfile == 1)
		{
			dup2(fd[1], STDOUT_FILENO);
			ft_dprintf("fd[1] (%d) is closed IN CHILD\n", fd[1]);
			close(fd[1]);
		}
		else
		{
			dup2(comm_info->fd_outfile, STDOUT_FILENO);
			ft_dprintf("comm_info->fd_outfile (%d) is closed IN CHILD\n", comm_info->fd_outfile);
			close(comm_info->fd_outfile);
		}
	}
	if (check_builtin_other(comm_info))
	{
		exe_other_builtin(comm_info, big);
		//close(comm_info->fd_outfile);
		/// new new new!!!!!!!!!!!!!!!!
		// close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
		call_cmd(comm_info->cmd, big->env);
	///// NEW NEW NEW !!!!!!! If there was no execution... 
	// Cleanup fds.
	// if (comm_info->fd_outfile > 2)
	// 	close(comm_info->fd_outfile);
	close(fd[1]);

	//ft_dprintf("pipes fd[1] %d is closed IN CHILD\n", fd[1]);

	/// NEW NEW NEW part of call_cmd
	exit(127);
	return (0);
}

/**
 * @brief This function starts the execution of a (binary) command
 * (every string from t_data-cmd, that wasn't defined as builtin command).
 *
 * @param comm_info struct with all necessary infos to
 * execute a single command
 *
 * @param c_i_next - next comm_info struct
 *
 * @param big struct with environmental variables, exit_code integer,
 * and count_commds size_t.
 */
int	execute(t_data *comm_info, t_data *c_i_next, t_big *big)
{
	pid_t pid;
	int fd[2];

	if (pipe(fd) == -1)
		w_errpipe_close(comm_info->fd_infile);
	signal(SIGINT, SIG_IGN);

	printf("fd->infile is %d\n", comm_info->fd_infile);
	printf("fd->outfile is %d\n", comm_info->fd_outfile);

	pid = fork();
	if (pid == -1)
		w_errfork_close(comm_info->fd_infile, fd);
	if (pid == 0)
	{
		if (child(comm_info, c_i_next, big, fd) == -1)
			return (-1);
	}
	else if (pid != 0)
	{
		close(fd[1]);

		printf("pipes fd[1] (fd %d) is closed IN PARENT\n", fd[1]);

		if (c_i_next != NULL)
		{
			//// NEW NEW NEW !!!!!!!!!!!!!!!!!!!!!!!!!
			if (comm_info->fd_outfile > 1)
			{
				close(fd[0]);
				//printf("pipes fd[0] (fd %d) is closed IN PARENT\n", fd[0]);
			}
			else if (comm_info->fd_outfile == 1 && c_i_next->fd_infile == 0)
			{
				ft_dprintf("Sending pipe_fd to next pipe...\n");
				ft_dprintf("c_i_next->fd_infile: %d\n", c_i_next->fd_infile);
				ft_dprintf("fd[0]: %d\n", fd[0]);
				c_i_next->fd_infile = fd[0];
				ft_dprintf("c_i_next->fd_infile: %d\n", c_i_next->fd_infile);
			}
			else if (comm_info->fd_outfile > 1 && c_i_next->fd_infile == 0)
			{
				close(fd[0]);
				c_i_next->fd_infile = open("/dev/null", O_RDONLY);
			}
		}
		else if (c_i_next == NULL)
		{
			printf("pipes fd[0] (fd %d) is closed in PARENT\n", fd[0]);
			close(fd[0]);
		}
	}
	comm_info->id = pid;
	return (0);
}
