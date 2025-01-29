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
 * t_data struct and deletes temporay heredoc-files (at /dev/)
 * before next iteration of the executer loop.
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

/**
 * @brief function that checks if command is a child-builtin 
 * (echo, pwd, env, help, export (only sort!))
 * and if the command is valid
 * (if not: manipulates the following 
 * command struct to have an infile with null input, if there is one)
 */
static void	exe_bin_ch_built_inval(t_big *big, t_data *comm_info, 
	t_data *comm_info_next)
{
	if (check_child_builtin(comm_info))
		fork_and_exe_child_builtin(comm_info, comm_info_next, big);
	else if (is_valid_cmd_and_print_err(comm_info->cmd, big))
	{
		fork_and_exe_binary(comm_info, comm_info_next, big);
	}
	else
	{
		if (comm_info_next && comm_info_next->fd_infile == 0)
			comm_info_next->fd_infile = open("/dev/null", O_RDONLY);
		fork_and_exe_binary(comm_info, comm_info_next, big);
	}
}

/**
 * @brief this function iterates through all commands,
 * checking if command has correct input / output data,
 * if it is a parent-builtin or child-builtin/binary
 * 
 * special case
 * > if the current command to execute is a parent-builtin
 * (builtins that are not executed in a child process) OR
 * > if there is an infile or outfile error in current command struct
 * AND the at the same 
 * time there is no infile defined to read from for next command in pipe line
 * (which would overwrite the pipe's end): manipulates the following 
 * command struct to have an infile with null input (/dev/null)
 * WHY @MARYNA?
 * 
 * @param big a struct that keeps all relevant information to run the 
 * minishell and execute command line inputs
 * @param curr a linked list with all commands (big->cmdlst) and its 
 * necessary infomation to execute the command
 */
static void	ft_executer_loop(t_big *big, t_list *curr)
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
				exe_parent_builtin(comm_info, big);
			}
			else
				exe_bin_ch_built_inval(big, comm_info, comm_info_next);
		}
		ft_executer_fd_close(comm_info);
		curr = curr->next;
	}
}

/**
 * @brief function to organise the execution part
 * 1st it checks for builtin-functions
 * 2nd if there are no it prints out the command details
 * (2nd part has to be overwritten by execution-part)
 *
 * @param big structure that holds all importand information
 * for execution part like cmdlist, env, last exit status
 */
int	ft_executer(t_big *big)
{
	int		exit_status_binary;
	t_list	*curr;

	exit_status_binary = -100;
	curr = big->cmdlist;
	ft_executer_loop(big, curr);
	exit_status_binary = get_exit_status_waitpid(big);
	assign_exit_code(big->cmdlist, exit_status_binary, big);
	return (0);
}
