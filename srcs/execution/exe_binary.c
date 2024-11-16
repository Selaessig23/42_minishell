
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

void	setup_and_exe_binary_in_child(t_data *comm_info, t_data *c_i_next, t_big *big)
{
	ft_handle_signals_childs();

	setup_input_output(comm_info, c_i_next);
	fd_cleanup_read_end_in_child(big);
	if (c_i_next == NULL && comm_info->fd_infile == 0 && comm_info->fd_outfile == 1)
	{
		exe_child_binary(comm_info->cmd, big->env);
		//fd_cleanup_in_child(big, comm_info, fd[1]);
	}
	else
	{
		exe_child_binary(comm_info->cmd, big->env);
		//fd_cleanup_in_child(big, comm_info, fd[1]);
	}
	fd_cleanup_in_child(big);
	exit(127);
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
int	fork_and_exe_binary(t_data *comm_info, t_data *c_i_next, t_big *big)
{
	pid_t pid;
	// int fd[2];

	// if (pipe(fd) == -1)
	// 	w_errpipe_close(comm_info->fd_infile);
	// comm_info->fd_pipe[0] = fd[0];
	// comm_info->fd_pipe[1] = fd[1];

	if (pipe(comm_info->fd_pipe) == -1)
		w_errpipe_close(comm_info->fd_infile);

	signal(SIGINT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN); // new new new
	pid = fork();
	if (pid == -1)
		w_errfork_close(comm_info->fd_infile, comm_info->fd_pipe);
	if (pid == 0)
	{
		setup_and_exe_binary_in_child(comm_info, c_i_next, big);
	}

	close(comm_info->fd_pipe[1]);

	// this is must be after fork... WHY?
	if (c_i_next != NULL)
	{
		if (comm_info->fd_outfile == 1 && c_i_next->fd_infile == 0)
			c_i_next->fd_infile = dup(comm_info->fd_pipe[0]);
		else if (comm_info->fd_outfile > 1 && c_i_next->fd_infile == 0)
			c_i_next->fd_infile = open("/dev/null", O_RDONLY);
	}
	
	close(comm_info->fd_pipe[0]);

	comm_info->id = pid;
	return (0);
}
