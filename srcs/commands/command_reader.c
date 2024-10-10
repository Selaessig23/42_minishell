
#include "minishell.h"

/**
 * DESCRIPTION:
 * file to read from cmdlist and organises execution of 
 * builtin-functions as well as system-fuctions (binaries)
 */

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
static int	dev_null(int read_from)
{
	int	new_read_from;

	close(read_from);
	new_read_from = open("/dev/null", O_RDONLY);
	return (new_read_from);
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
static void	ft_builtin_executer(t_data *comm_info, t_big *big, char *prompt)
{
	char	**argv;

	argv = comm_info->cmd;
	if (argv[0] && !ft_strncmp(argv[0], "echo", ft_strlen(argv[0]))
		&& ft_strlen(argv[0]) == ft_strlen("echo"))
		ft_echo(comm_info, big);
	else if (argv[0] && !ft_strncmp(argv[0], "cd", ft_strlen(argv[0]))
		&& ft_strlen(argv[0]) == ft_strlen("cd"))
		ft_cd(big, argv);
	else if (argv[0] && !ft_strncmp(argv[0], "pwd", ft_strlen(argv[0]))
		&& ft_strlen(argv[0]) == ft_strlen("pwd"))
		ft_print_pwd(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "export", ft_strlen(argv[0]))
		&& ft_strlen(argv[0]) == ft_strlen("export"))
		ft_export(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "unset", ft_strlen(argv[0]))
		&& ft_strlen(argv[0]) == ft_strlen("unset"))
		ft_unset(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "env", ft_strlen(argv[0]))
		&& ft_strlen(argv[0]) == ft_strlen("env"))
		ft_print_env(comm_info, big);
	else if (argv[0] && !ft_strncmp(argv[0], "exit", ft_strlen(argv[0]))
		&& ft_strlen(argv[0]) == ft_strlen("exit"))
		ft_exit_minishell(comm_info, big, prompt);
	else if (argv[0] && !ft_strncmp(argv[0], "help", ft_strlen(argv[0]))
		&& ft_strlen(argv[0]) == ft_strlen("help"))
		ft_minishell_help(comm_info->fd_outfile);
}

/**
 * @brief function to check for built-in-commands
 * 
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
static int	ft_builtin_checker(t_data *comm_info)
{
	char	**argv;

	argv = comm_info->cmd;
	if (argv[0] 
		&& ((!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) 
				&& ft_strlen(argv[0]) == ft_strlen("echo"))
			|| (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0]))
				&& ft_strlen(argv[0]) == ft_strlen("cd"))
			|| (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0]))
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
int	ft_executer(t_big *big, char *prompt)
{
	t_list	*curr;
	t_data	*comm_info;
	t_data	*comm_info_next;

	curr = big->cmdlist;
	comm_info = curr->content;
	comm_info_next = (t_data *)curr->next;
	// set_pipes(t_big *big);
	// t_list	*curr;
	// t_data	*comm_info;
	// curr = big->cmdlist;
	// comm_info = curr->content;
	// int			fd[2];
	// a bunch of if statements
	// if (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
	// {
	// 	printf("fd_infile OR fd_outfile is /dev/null\n");
	// 	comm_info->fd_infile = dev_null(comm_info->fd_infile);
	// 	printf("fd_infile: %d\n", comm_info->fd_infile);
	// }
	// How to not close pipes....
	while (curr != NULL)
	{
		comm_info = curr->content;
		printf("\ncommand number: %zu\n", comm_info->commands_no);
		printf("fd_infile: %d\n", comm_info->fd_infile);
		if (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
		{
			//printf("fd_infile OR fd_outfile is /dev/null\n");
			//comm_info->fd_infile = dev_null(comm_info->fd_infile);
			//printf("fd_infile: %d\n", comm_info->fd_infile);
			printf("EXIT WITH ERROR\n");
		}
		else if (ft_builtin_checker(comm_info))
		{
			ft_builtin_executer(comm_info, big, prompt);
			//printf("---------------------------------------------\n");
			// return (1);
		}
		else
		{
			//ft_test_command_print(prompt, comm_info, big);
			
			// if the command invalid - displays an error
			// if it is the last command - exit status
			// if it is not the last command and the next pipe
			// else
			ft_binar_exe(comm_info, comm_info_next, big);
		}
		// printf("fd infile: %i, fd outfile: %i\n", comm_info->fd_infile, comm_info->fd_outfile);
		if (comm_info->fd_infile > 2)
			close(comm_info->fd_infile);
		if (comm_info->in_heredoc == true)
			delete_heredoc(comm_info);
		if (comm_info->fd_outfile > 2)
			close(comm_info->fd_outfile);
		curr = curr->next;
	}
	/// wait pid function.
	/// extract exit status
	ft_free_cl(&(big->cmdlist));
	big->count_commds = 0;
	return (0);
}
