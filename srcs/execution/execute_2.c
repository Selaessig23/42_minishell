#include "minishell.h"

void	setup_input_output(t_data *comm_info, t_data *c_i_next)
{
	if (c_i_next == NULL)
	{
		if (comm_info->fd_infile == 0 && comm_info->fd_outfile == 1)
			return ;
	}
	if (c_i_next != NULL)
	{
		if (comm_info->fd_outfile == 1) 
			dup2(comm_info->fd_pipe[1], STDOUT_FILENO);
	}
	if (comm_info->fd_infile > 0)
		dup2(comm_info->fd_infile, STDIN_FILENO);
	if (comm_info->fd_outfile > 1)
		dup2(comm_info->fd_outfile, STDOUT_FILENO);
	
}

void	fd_cleanup_read_end_in_child(t_big *big)
{
	t_list	*linked_list;
	t_data	*comm_info;

	linked_list = big->cmdlist;
	comm_info = NULL;
	while (linked_list != NULL)
	{
		comm_info = linked_list->content;
		if (comm_info->fd_pipe[0] > 2)
		{
			close(comm_info->fd_pipe[0]);
		}
		linked_list = linked_list->next;
	}
}

/**
 * Closing all opened file descriptors that we don't need in 
 * child procces. Current node is in used, so closing from the
 * next node if it is not NULL.
 */
/// WARNING // 	close_fd_with_error_handling();
void	fd_cleanup_in_child(t_big *big)
{
	t_list	*linked_list;
	t_data	*comm_info;

	linked_list = big->cmdlist;
	comm_info = NULL;
	while (linked_list != NULL)
	{
		comm_info = linked_list->content;
		if (comm_info->fd_infile > 2)
			close(comm_info->fd_infile);
		if (comm_info->fd_outfile > 2)
			close(comm_info->fd_outfile);
		if (comm_info->fd_pipe[1] > 2)
			close(comm_info->fd_pipe[1]);
		linked_list = linked_list->next;
	}
}

/**
 * This function is a wrapper for the waitpid system call, designed to wait
 * for the termination of multiple child processes stored in a linked list.
 * It ensures that each child process is waited on, handling process
 * management efficiently.
 *
 * This function iterates through a linked list of process IDs (pids)
 * stored in the "comm_info structure" and calls waitpid on each one
 * to wait for their termination.
 *
 * @param big->cmdlist: A pointer to a "comm_info" structure containing
 * the list of process IDs to wait for.
 */
// This macro WIFEXITED returns true if the child process
// exited normally.
int	w_waitpid(t_big *big)
{
	t_list *curr;
	t_data *comm_info;
	int exitcode;
	int status;
	bool	signaled;

	signaled = false;
	exitcode = 0;
	status = -1;
	curr = big->cmdlist;
	while (curr != NULL)
	{
		comm_info = curr->content;
		/// NEW
		if (comm_info->id != -1)
			waitpid(comm_info->id, &status, 0);
		if (WIFSIGNALED(status))
		{
			if ((WTERMSIG(status) == 2 || WTERMSIG(status) == 3) && !signaled)
			{
				if (WTERMSIG(status) == 3)
					ft_dprintf("Quit (core dumped)");
				signaled = true;
				exitcode = 128 + WTERMSIG(status);
				write(2, "\n", 1);
			}
		}
		curr = curr->next;
	}
	if (status >= 0)
	{
		if (WIFEXITED(status))
			exitcode = WEXITSTATUS(status);
	}
	return (exitcode);
}
