/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:39:56 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/10 19:39:56 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * file to read from cmdlist and organises execution of
 * builtin-functions as well as system-fuctions (binaries)
 */
/**
 * Closing file descriptors in parent process in current
 * t_data struct before next iteration of the executer loop.
 */
static void	ft_executer_fd_close(t_data	*comm_info)
{
	if (comm_info->fd_infile > 2)
		close(comm_info->fd_infile);
	if (comm_info->fd_outfile > 2)
		close(comm_info->fd_outfile);
	if (comm_info->in_heredoc == true)
		delete_heredoc(comm_info);
}

static void	process_binary_and_child_builtin(t_big *big, t_data	*comm_info, t_data *comm_info_next)
{
	if (check_child_builtin(comm_info))
		fork_and_exe_child_builtin(comm_info, comm_info_next, big);
	else if (is_valid_cmd_and_print_err(comm_info->cmd, big))
	{
		fork_and_exe_binary(comm_info, comm_info_next, big);
	}
	else
	{
		// for case `catttt | grep "hello"` etc.
		if (comm_info_next && comm_info_next->fd_infile == 0)
			comm_info_next->fd_infile = open("/dev/null", O_RDONLY);
		fork_and_exe_binary(comm_info, comm_info_next, big);
	}
}

static void	ft_executer_loop(t_big *big, t_list *curr, char *prompt)
{
	t_data	*comm_info_next;
	t_data	*comm_info;

	while (curr != NULL)
	{
		comm_info = curr->content;
		comm_info_next = ft_pointer_next_command(curr);
		if (comm_info->cmd[0] != NULL)
		{
			if (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
				exe_fd_error(big, comm_info_next);
			else if (check_parent_builtin(comm_info))
			{
				if (comm_info_next && comm_info_next->fd_infile == 0)
					comm_info_next->fd_infile = open("/dev/null", O_RDONLY);
				exe_parent_builtin(comm_info, big, prompt);
			}
			else
				process_binary_and_child_builtin(big, comm_info, comm_info_next);
		}
		ft_executer_fd_close(comm_info);
		curr = curr->next;
	}
}

/**
 * @brief function to organises the execution part
 * 1st it checks for builtin-functions
 * 2nd if there are no it prints out the command details
 * (2nd part has to be overwritten by execution-part)
 *
 * @param big structure that holds all importand information
 * for execution part like cmdlist, env, last exit status
 * @param prompt string that has to be freed in case of builtin exit
 */
int ft_executer(t_big *big, char *prompt)
{
	int		exit_status_binary;
	t_list	*curr;

	exit_status_binary = -100;
	curr = big->cmdlist;
	ft_executer_loop(big, curr, prompt);
	exit_status_binary = w_waitpid(big);
	assign_exit_code(big->cmdlist, exit_status_binary, big);
	ft_free_cl(&(big->cmdlist));
	big->count_commds = 0;
	return (0);
}
