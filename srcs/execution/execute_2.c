#include "minishell.h"


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
