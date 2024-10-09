
#include "minishell.h"

// waitpid(pid2, &status, 0);
// 		if (WIFEXITED(status))
// 			exitcode = WEXITSTATUS(status);

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
void    ft_binar_exe(t_data *comm_info, t_data *c_i_next, t_big *big)
{
    pid_t		pid;
    int			fd[2];
    
    //w_dup2(comm_info->fd_infile, STDIN_FILENO, -2);
    if (pipe(fd) == -1)
		w_errpipe_close(comm_info->fd_infile);
    pid = fork();
    if (pid == -1)
		w_errfork_close(comm_info->fd_infile, comm_info->fd_outfile);
    if (pid == 0)
	{
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        //call_cmd(///);
    }
    else if (pid != 0)
    {
        close(fd[1]);
        w_dup2(comm_info->fd_infile, STDIN_FILENO, -2);
        //dup2((*ch)->fd_to_read, STDIN_FILENO);
        close(comm_info->fd_infile);
        if (c_i_next != NULL)
        {
            // output to pipe and input from prev pipe.
            if (comm_info->fd_outfile == 1 && c_i_next->fd_infile == 0)
            c_i_next->fd_infile == fd[0];
        }
        else if (c_i_next != NULL)
        {
            // If it is the last pipe and there is no output redirection
            // send a write enf of the pipe to STDOUT - to display on Terminal.
        }  
    }
    comm_info->id = pid;
}
