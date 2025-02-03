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

/**
 * @brief function to setup the pipe and infile handling of 
 * child processes depending on the the command struct of next command
 * 1) if there is no outfile in current command and if there exists 
 * a next command than write output to (write end of) pipe[1] 
 * instead of using STDOUT
 * 2) if there is an infile for current command, send it to STDIN
 * 3) if there is an outfile for current command, sebd STDOUT to outfile
 */
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

/**
 * @brief function to close all file descriptors 
 * stored in the read end of the pipe by iterating 
 * through the linked lists of commands and closing the
 * read end of each command struct (fd_pipe[0])
 */
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
