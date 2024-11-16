/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_built-ins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:43:45 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/16 06:53:16 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export, unset, cd, exit
// execution IF exe is true
// if exe is false - checking for errors and exit assigns exit code
void exe_parent_builtin(t_data *comm_info, t_big *big, char *prompt)
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0])
	{
		if (is_exact_string(argv[0], "cd"))
			ft_cd(big, argv);
		else if (is_exact_string(argv[0], "export"))
			ft_export(big, comm_info);
		else if (is_exact_string(argv[0], "unset"))
			ft_unset(big, comm_info);
		else if (is_exact_string(argv[0], "exit"))
			ft_exit_minishell(comm_info, big, prompt);
		else if (is_exact_string(argv[0], "help"))
			ft_minishell_help(comm_info, big);
	}
}

/**
 * @brief function to organise execution of built-in-commands
 *
 * @param comm_info struct with all necessary infos to
 * execute a single command
 * @param big big struct with all command infos
 * that are required for executing builtins or
 * that have to be freed in case of builtin exit
 * @param prompt string that has to be freed in case of builtin exit
 */
void exe_child_builtin(t_data *comm_info, t_big *big)
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0])
	{
		if (is_exact_string(argv[0], "echo"))
			ft_echo(comm_info, big);
		else if (is_exact_string(argv[0], "pwd"))
			ft_print_pwd(big, comm_info);
		else if (is_exact_string(argv[0], "env"))
			ft_print_env(comm_info, big);
		else if (is_exact_string(argv[0], "help"))
			ft_minishell_help(comm_info, big);
	}
}

void	setup_and_exe_builtin_in_child(t_data *comm_info, t_data *c_i_next, t_big *big)
{
	ft_handle_signals_childs();
	
	setup_input_output(comm_info, c_i_next);
	fd_cleanup_read_end_in_child(big); /// new
	if (c_i_next == NULL)
	{
		if (comm_info->fd_infile == 0 && comm_info->fd_outfile == 1)
		{
			exe_child_builtin(comm_info, big);
			fd_cleanup_in_child(big);
			// 	close_fd_with_error_handling();
			exit(EXIT_SUCCESS);
		}
	}
	exe_child_builtin(comm_info, big);
	fd_cleanup_in_child(big);
	exit(EXIT_SUCCESS);
}

int	fork_and_exe_child_builtin(t_data *comm_info, t_data *c_i_next, t_big *big)
{
	pid_t pid;
	// int fd[2];

	// if (pipe(fd) == -1)
	// 	w_errpipe_close(comm_info->fd_infile);
	// comm_info->fd_pipe[0] = fd[0];
	// comm_info->fd_pipe[1] = fd[1];

	if (pipe(comm_info->fd_pipe) == -1)
		w_errpipe_close(comm_info->fd_infile);
	
	
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		w_errfork_close(comm_info->fd_infile, comm_info->fd_pipe);
	if (pid == 0)
	{
		setup_and_exe_builtin_in_child(comm_info, c_i_next, big);
	}
	
	close(comm_info->fd_pipe[1]);

	if (c_i_next != NULL)
	{
		if (comm_info->fd_outfile == 1 && c_i_next->fd_infile == 0)
			c_i_next->fd_infile = dup(comm_info->fd_pipe[0]);
			//c_i_next->fd_infile = dup(fd[0]);
		else if (comm_info->fd_outfile > 1 && c_i_next->fd_infile == 0)
			c_i_next->fd_infile = open("/dev/null", O_RDONLY);
	}

	if (comm_info->fd_pipe[0] > 2)
		close(comm_info->fd_pipe[0]);
		
	comm_info->id = pid;
	return (0);
}
