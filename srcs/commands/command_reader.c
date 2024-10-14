
#include "minishell.h"

/**
 * DESCRIPTION:
 * file to read from cmdlist and organises execution of
 * builtin-functions as well as system-fuctions (binaries)
 */

/**
 * Prints an error message to standard error when a command is not found 
 * in the system's executable paths.
 * 
 * @param cmd_plus_args[0] The first element of **cmd_plus_args 
 * is the command.
 */
void	no_cmd_path(char **cmd_plus_args)
{
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd_plus_args[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * It explicitly prints an error message 
 * (via "no_cmd_path") if the command cannot be found.
 */
static int	check_cmd(char **cmd_plus_args, char *env[])
{
	char	*cmd_path;

	if (access(cmd_plus_args[0], F_OK | X_OK) == 0)
		return (0);
	cmd_path = get_path(cmd_plus_args[0], env);
	if (!cmd_path)
	{
		no_cmd_path(cmd_plus_args);
		return (1);
	}
	else
	{
		free(cmd_path);
		return (0);
	}
}

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
static int dev_null(int read_from)
{
	if (read_from > 0)
		close(read_from);
	read_from = open("/dev/null", O_RDONLY);
	return (read_from);
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
static void ft_builtin_executer(t_data *comm_info, t_big *big, char *prompt)
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0] && !ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("echo"))
		ft_echo(comm_info, big);
	else if (argv[0] && !ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("cd"))
		ft_cd(big, argv);
	else if (argv[0] && !ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("pwd"))
		ft_print_pwd(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "export", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("export"))
		ft_export(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("unset"))
		ft_unset(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "env", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("env"))
		ft_print_env(comm_info, big);
	else if (argv[0] && !ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("exit"))
		ft_exit_minishell(comm_info, big, prompt);
	else if (argv[0] && !ft_strncmp(argv[0], "help", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("help"))
		ft_minishell_help(comm_info->fd_outfile);
}

/**
 * @brief function to check for built-in-commands
 *
 * @param comm_info struct with all necessary infos to
 * execute a single command
 */
static int ft_builtin_checker(t_data *comm_info)
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0] && ((!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("echo")) || (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("cd")) || (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("pwd")) || (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("export")) || (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("unset")) || (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("env")) || (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("exit")) || (!ft_strncmp(argv[0], "help", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("help"))))
		return (1);
	else
		return (0);
}

// Restore STDIN if it was changed before
// If you redirected STDIN, reset it back to original terminal
static void	restore_stdin()
{
	int	terminal_fd;

	terminal_fd = open("/dev/tty", O_RDONLY);
	if (terminal_fd == -1)
			error_handling(1);
	dup2(terminal_fd, STDIN_FILENO);
	close(terminal_fd);
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

	curr = big->cmdlist;
	comm_info = curr->content;
	while (curr != NULL)
	{
		comm_info = curr->content;
		if (curr->next != NULL)
			comm_info_next = curr->next->content;
		else
			comm_info_next = NULL;
		if (comm_info->cmd[0] == NULL)
			printf("Pipe #%zu has NO command\n", comm_info->commands_no);
		else if (comm_info->cmd[0] != NULL)
		{
			if (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
			{
				printf("EXIT WITH ERROR\n");
			}
			else if (ft_builtin_checker(comm_info))
				ft_builtin_executer(comm_info, big, prompt);
			else if (check_cmd(comm_info->cmd, big->env))
			{
				// command does not exist. what exit status?
				big->exit_code = 127;
				// if(comm_info_next && comm_info_next->fd_infile == 0)
				// 	comm_info_next->fd_infile = dev_null_for_zero(comm_info_next->fd_infile);
			}
			else
			{
				// ft_test_command_print(prompt, comm_info, big);
				ft_binar_exe(comm_info, comm_info_next, big);
			}
			// printf("fd infile: %i, fd outfile: %i\n", comm_info->fd_infile, comm_info->fd_outfile);
		}
		if (comm_info->fd_infile > 2)
			close(comm_info->fd_infile);
		if (comm_info->in_heredoc == true)
			delete_heredoc(comm_info);
		if (comm_info->fd_outfile > 2)
			close(comm_info->fd_outfile);
		curr = curr->next;
	}
	w_waitpid(big);
	restore_stdin();
	/// extract exit status
	ft_free_cl(&(big->cmdlist));
	big->count_commds = 0;
	return (0);
}
