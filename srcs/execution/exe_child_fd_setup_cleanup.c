/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child_fd_setup_cleanup.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:30:43 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 22:30:43 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_input_output_in_child(t_data *comm_info, t_data *c_i_next)
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
