#include "minishell.h"

void	setup_input_output(t_data *comm_info, t_data *c_i_next, int fd_write_end)
{
	if (comm_info->fd_infile > 0)
		dup2(comm_info->fd_infile, STDIN_FILENO);
	if (comm_info->fd_outfile > 1)
		dup2(comm_info->fd_outfile, STDOUT_FILENO);
	if (c_i_next != NULL)
	{
		if (comm_info->fd_outfile == 1)
			dup2(fd_write_end, STDOUT_FILENO);
	}
}

/**
 * Closing all opened file descriptors that we don't need in 
 * child procces. Current node is in used, so closing from the
 * next node if it is not NULL.
 */
void	fd_cleanup_in_child(t_big *big, int fd_write_end)
{
	t_list	*linked_list;
	t_data	*node;

	linked_list = big->cmdlist;
	node = NULL;
	// while (linked_list != NULL)
	// {
	// 	node = linked_list->content;
	// 	if (node == to_close_fd)
	// 		break ;
	// 	// if (node != to_close_fd)
	// 	linked_list = linked_list->next;
	// }
	while (linked_list != NULL)
	{
		node = linked_list->content;
		if (node->fd_infile > 2)
			close(node->fd_infile);
		if (node->fd_outfile > 2)
		{
			//ft_dprintf("%d is closed in child\n", node->fd_outfile);
			close(node->fd_outfile);
		}
		linked_list = linked_list->next;
	}
	//ft_dprintf("closing pipe %d in a child\n", fd_write_end);
	if (close(fd_write_end) == -1)
	{
		close_fd_with_error_handling();
	}
}

/**
 * Closing all opened file descriptors that we don't need in 
 * child procces. Current node is in used, so closing from the
 * next node if it is not NULL.
 */
void	fd_cleaning_child(t_big *big, t_data *to_close_fd)
{
	t_list	*linked_list;
	t_data	*node;

	linked_list = big->cmdlist->next;
	node = NULL;
	while (linked_list != NULL)
	{
		node = linked_list->content;
		if (node != to_close_fd)
			linked_list = linked_list->next;
		else if (node == to_close_fd)
			break ;
	}
	while (linked_list != NULL)
	{
		node = linked_list->content;
		if (node->fd_infile > 2)
			close(node->fd_infile);
		if (node->fd_outfile > 2)
			close(node->fd_outfile);
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
