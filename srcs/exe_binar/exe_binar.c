
#include "minishell.h"

// waitpid(pid2, &status, 0);
// 		if (WIFEXITED(status))
// 			exitcode = WEXITSTATUS(status);

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
	exit (EXIT_FAILURE);
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

/**
 * @brief This function starts the execution of a binary command
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
void	ft_binar_exe(t_data *comm_info, t_data *c_i_next, t_big *big)
{
	pid_t		pid;
    int			fd[2];
    
    if (pipe(fd) == -1)
		w_errpipe_close(comm_info->fd_infile);
    pid = fork();
    if (pid == -1)
		w_errfork_close(comm_info->fd_infile, fd);
    if (pid == 0)
	{
        close(fd[0]);
        dup2(comm_info->fd_outfile, STDOUT_FILENO);
		close(fd[1]);
		//close(comm_info->fd_outfile);
        call_cmd(comm_info->cmd, big->env);
    }
    else if (pid != 0)
    {
        close(fd[1]);
		//w_dup2(comm_info->fd_infile, STDIN_FILENO, -2);
		//w_dup2(fd[0], STDIN_FILENO, -2);
		printf("id_infile: %d\n", comm_info->fd_infile);
		if (comm_info->fd_infile != 0)
		{
			w_dup2(comm_info->fd_infile, STDIN_FILENO, -2);
			close(comm_info->fd_infile);
		}
		if (c_i_next != NULL)
        {
            if (comm_info->fd_outfile == 1 && c_i_next->fd_infile == 0)
            	c_i_next->fd_infile = fd[0];
        }
        else if (c_i_next == NULL)
			printf("ft_binar_exe. c_i_next == NULL\n");
		close(fd[0]);
		waitpid(pid, NULL, 0);
		
    }
    comm_info->id = pid;
}
