
#include "minishell.h"
#include <sys/stat.h>

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
static int	no_cmd_path(char **cmd_plus_args)
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
static int	check_cmd(char **cmd_plus_args, char *env[])
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
		if (no_cmd_path(cmd_plus_args))
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

// export, unset, cd, exit
static void ft_builtin_exe_lstcmd(t_data *comm_info, t_big *big, char *prompt)
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0] && !ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("cd"))
		ft_cd(big, argv);
	else if (argv[0] && !ft_strncmp(argv[0], "export", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("export"))
		ft_export(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("unset"))
		ft_unset(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("exit"))
		ft_exit_minishell(comm_info, big, prompt);
	else if (argv[0] && !ft_strncmp(argv[0], "help", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("help"))
		ft_minishell_help(comm_info->fd_outfile);
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
void ft_builtin_executer(t_data *comm_info, t_big *big) // char *prompt
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0] && !ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("echo"))
		ft_echo(comm_info, big);
	// else if (argv[0] && !ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("cd"))
	// 	ft_cd(big, argv);
	else if (argv[0] && !ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("pwd"))
		ft_print_pwd(big, comm_info);
	// else if (argv[0] && !ft_strncmp(argv[0], "export", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("export"))
	// 	ft_export(big, comm_info);
	// else if (argv[0] && !ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("unset"))
	// 	ft_unset(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "env", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("env"))
		ft_print_env(comm_info, big);
	// else if (argv[0] && !ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("exit"))
	// 	ft_exit_minishell(comm_info, big, prompt);
	else if (argv[0] && !ft_strncmp(argv[0], "help", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("help"))
		ft_minishell_help(comm_info->fd_outfile);
}

static int ft_builtin_lstcmd_checker(t_data *comm_info)
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0] != NULL &&
		((!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("cd")) 
		|| (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("export")) 
		|| (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("unset")) 
		|| (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("exit")) 
		|| (!ft_strncmp(argv[0], "help", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("help"))))
		return (1);
	else
		return (0);
}

/**
 * @brief function to check for built-in-commands
 *
 * @param comm_info struct with all necessary infos to
 * execute a single command
 */
int	ft_builtin_checker(t_data *comm_info)
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0] && ((!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) && 
		ft_strlen(argv[0]) == ft_strlen("echo")) || (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) 
			&& ft_strlen(argv[0]) == ft_strlen("cd")) || (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) 
				&& ft_strlen(argv[0]) == ft_strlen("pwd")) 
					|| (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])) 
						&& ft_strlen(argv[0]) == ft_strlen("export")) 
							|| (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) 
								&& ft_strlen(argv[0]) == ft_strlen("unset")) 
									|| (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])) 
										&& ft_strlen(argv[0]) == ft_strlen("env")) 
											|| (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) 
												&& ft_strlen(argv[0]) == ft_strlen("exit")) 
													|| (!ft_strncmp(argv[0], "help", ft_strlen(argv[0])) 
														&& ft_strlen(argv[0]) == ft_strlen("help"))))
		return (1);
	else
		return (0);
}

// Restore STDIN if it was changed before
// If you redirected STDIN, reset it back to original terminal
// static void	restore_stdin()
// {
// 	int	terminal_fd;

// 	terminal_fd = open("/dev/tty", O_RDONLY);
// 	if (terminal_fd == -1)
// 			error_handling(1);
// 	dup2(terminal_fd, STDIN_FILENO);
// 	close(terminal_fd);
// }

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
		if (!ft_builtin_lstcmd_checker(data))
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
	t_list *curr;
	t_data *comm_info;
	t_data *comm_info_next;
	int		exit_status_binary;

	exit_status_binary = -100;
	curr = big->cmdlist;
	comm_info = curr->content;
	while (curr != NULL)
	{
		comm_info = curr->content;
		if (curr->next != NULL)
			comm_info_next = curr->next->content;
		else
			comm_info_next = NULL;
		if (comm_info->cmd[0] != NULL)
		{
			if (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
			{
				big->exit_code = 1;
				if (comm_info_next && comm_info_next->fd_infile == 0)
					comm_info_next->fd_infile = open("/dev/null", O_RDONLY);
			}
			else if (ft_builtin_lstcmd_checker(comm_info))
			{
				if (big->count_commds == comm_info->commands_no)
					ft_builtin_exe_lstcmd(comm_info, big, prompt);
				else if (comm_info_next && comm_info_next->fd_infile == 0)
					comm_info_next->fd_infile = open("/dev/null", O_RDONLY);
			}
			else if (big->count_commds == comm_info->commands_no && ft_builtin_checker(comm_info))
				ft_builtin_executer(comm_info, big);
			else
			{
				if (!check_cmd(comm_info->cmd, big->env))
					ft_binar_exe(comm_info, comm_info_next, big);
				else
					big->exit_code = 999;
			}
		}
		if (comm_info->fd_infile > 2)
			close(comm_info->fd_infile);
		if (comm_info->in_heredoc == true)
			delete_heredoc(comm_info);
		if (comm_info->fd_outfile > 2)
			close(comm_info->fd_outfile);
		curr = curr->next;
	}
	//restore_stdin();
	exit_status_binary = w_waitpid(big);
	assign_exit_code(big->cmdlist, exit_status_binary, big);
	ft_free_cl(&(big->cmdlist));
	big->count_commds = 0;
	//ft_dprintf("FINAL EXIT CODE: %d\n", big->exit_code);
	return (0);
}
