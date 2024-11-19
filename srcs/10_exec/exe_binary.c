/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 23:17:31 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/17 23:17:31 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (read_from > 2)
		close(read_from);
	read_from = open("/dev/null", O_RDONLY);
	return (read_from);
}

void	setup_and_exe_binary_in_child(t_data *comm_info, 
	t_data *c_i_next, t_big *big)
{
	int	exit_code;

	exit_code = -1;
	ft_handle_signals_childs();
	setup_input_output_in_child(comm_info, c_i_next);
	fd_cleanup_read_end_in_child(big);
	exit_code = exe_child_binary(comm_info->cmd, big->env);
	fd_cleanup_in_child(big);
	free_t_big(big);
	exit(exit_code);
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
	pid_t	pid;

	if (pipe(comm_info->fd_pipe) == -1)
		w_errpipe_close(comm_info->fd_infile);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		w_errfork_close(comm_info->fd_infile, comm_info->fd_pipe);
	if (pid == 0)
		setup_and_exe_binary_in_child(comm_info, c_i_next, big);
	close(comm_info->fd_pipe[1]);
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
