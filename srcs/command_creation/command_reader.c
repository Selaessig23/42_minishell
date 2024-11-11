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
 * @brief helper functin of no_cmd_path
 * st.st_mode & S_IFMT = 
 * This extracts the file type from the st_mode field by masking the mode bits 
 * with S_IFMT, which is the bitmask for the file type
*/
static int	ft_check_executable(char *executable)
{
	if (access(executable, F_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(executable, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (0);
	}
	else if (access(executable, R_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(executable, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

/**
 * Prints a specific error message to standard error 
 * when a command is not found in the system's executable paths.
 * 
 * @param cmd_plus_args[0] The first element of **cmd_plus_args 
 * is the command.
 */
static int	no_cmd_path(char **cmd_plus_args, char **binarypaths)
{
	if (!ft_strncmp(cmd_plus_args[0], "./", 2))
		return (ft_check_executable(cmd_plus_args[0]));
	else if (!ft_strncmp(cmd_plus_args[0], "/", 1))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_plus_args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
	}
	else
	{
		ft_check_defaultpath(cmd_plus_args[0], binarypaths);
		ft_putstr_fd(cmd_plus_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
	}

}

/**
 * It explicitly prints an error message 
 * (via "no_cmd_path") if the command cannot be found.
 */
static int	check_cmd(char **cmd_plus_args, char *env[], char **binarypaths)
{
	char	*cmd_path;
	struct stat check_dir;
    
	// Check if it's a directory
	if (stat((cmd_plus_args[0]), &check_dir) == 0)
	{
		// printf ("mhhh: %s\n", cmd_plus_args[0]);
		if ((!ft_strncmp(cmd_plus_args[0], "./", 2) || !ft_strncmp(cmd_plus_args[0], "/", 1))
			&& S_ISDIR(check_dir.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd_plus_args[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			return (1);
		}
		else if (S_ISDIR(check_dir.st_mode))
		{
			ft_putstr_fd(cmd_plus_args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found", STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
		return (0);
		}
	}
	if (access(cmd_plus_args[0], F_OK | X_OK) == 0)
		return (0);
	cmd_path = get_path(cmd_plus_args[0], env);
	if (!cmd_path)
	{
		if (no_cmd_path(cmd_plus_args, binarypaths))
			return (1);
		else
			return (0);
	}
	else
	{
		free(cmd_path);
		return (0);
	}
}

static void	assign_exit_code(t_list	*cmdlist, int exit_status_binar, t_big *big)
{
	t_data *data;

	data = (ft_lstlast(cmdlist))->content;
	if (big->exit_code == 999)
		big->exit_code = 126;
	else if (data->fd_infile < 0 || data->fd_outfile < 0)
		return ;
	else
	{
		if (!check_builtin_parent(data))
			big->exit_code = exit_status_binar;
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
	t_list	*curr;
	t_data	*comm_info;
	t_data	*comm_info_next;
	int		exit_status_binary;

	exit_status_binary = -100;
	curr = big->cmdlist;
	comm_info = curr->content;
	while (curr != NULL)
	{
		comm_info = curr->content;
		comm_info_next = ft_pointer_next_command(curr);
		if (comm_info->cmd[0] != NULL)
		{
			if (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
				exe_fd_error(big, comm_info_next);
			else if (check_builtin_parent(comm_info))
			{
				// !!! check this if statement. I'm not sure we need it.
				// if (comm_info_next && comm_info_next->fd_infile == 0)
				// 	comm_info_next->fd_infile = open("/dev/null", O_RDONLY);
				exe_parent_builtin(comm_info, big, prompt);
			}
			else if (big->count_commds == comm_info->commands_no && check_builtin_other(comm_info))
				exe_other_builtin(comm_info, big);
			else
			{
				ft_dprintf("execute\n");
				if (!check_cmd(comm_info->cmd, big->env, big->binarypaths))
					execute(comm_info, comm_info_next, big);
				else
					big->exit_code = 999;
			}
		}
		if (comm_info->fd_infile > 2)
			close(comm_info->fd_infile);
		if (comm_info->in_heredoc == true)
			delete_heredoc(comm_info);
		if (comm_info->fd_outfile > 2)
		{
			ft_dprintf("comm_info->fd_outfile (%d) is closed PARENT\n", comm_info->fd_outfile);
			close(comm_info->fd_outfile);
		}
		curr = curr->next;
	}
	exit_status_binary = w_waitpid(big);
	assign_exit_code(big->cmdlist, exit_status_binary, big);
	ft_free_cl(&(big->cmdlist));
	big->count_commds = 0;


	ft_dprintf("last line of ft_executer\n");
	return (0);
}
