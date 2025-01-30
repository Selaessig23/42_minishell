/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reader_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:23:23 by mpeshko           #+#    #+#             */
/*   Updated: 2025/01/29 16:59:42 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file exit code handling and signal handling of
 * child processes is organised
 */

void	assign_exit_code(t_list	*cmdlist, int exit_status_binar, t_big *big)
{
	t_data	*data;

	data = (ft_lstlast(cmdlist))->content;
	if (data->fd_infile < 0 || data->fd_outfile < 0)
		return ;
	else
	{
		if (!check_parent_builtin(data))
			big->exit_code = exit_status_binar;
	}
}

static int	w_waitpid(t_data *comm_info, int status, 
	bool *signaled, int *exitcode)
{
	if (comm_info->id != -1)
	{
		waitpid(comm_info->id, &status, 0);
		if (WIFSIGNALED(status))
		{
			if ((WTERMSIG(status) == 2 || WTERMSIG(status) == 3) && 
				*signaled == false)
			{
				if (WTERMSIG(status) == 3)
					ft_dprintf("Quit (core dumped)");
				*signaled = true;
				*exitcode = 128 + WTERMSIG(status);
				write(2, "\n", 1);
			}
		}
	}
	return (status);
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
 * This macro WIFEXITED returns true if the child process
 * exited normally.
 *
 * @param big->cmdlist: A pointer to a "comm_info" structure containing
 * the list of process IDs to wait for.
 */
int	get_exit_status_waitpid(t_big *big)
{
	t_list	*curr;
	int		exitcode;
	int		status;
	t_data	*comm_info;
	bool	signaled;

	exitcode = 0;
	status = -1;
	curr = big->cmdlist;
	signaled = false;
	while (curr != NULL)
	{
		comm_info = curr->content;
		status = w_waitpid(comm_info, status, &signaled, &exitcode);
		curr = curr->next;
	}
	if (status >= 0)
	{
		if (WIFEXITED(status))
			exitcode = WEXITSTATUS(status);
	}
	return (exitcode);
}
