
#include "minishell.h"

/**
 * DESCRIPTION:
 * file to read from cmdlist and organises execution of 
 * builtin-functions as well as system-fuctions (binaries)
 */

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
	if (argv[0] && !ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
	{
		printf("builtin function %s in testing mode\n", argv[0]);
		printf("---------------------------------------------\n");
		ft_echo(comm_info, big);
	}
	else if (argv[0] && !ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
	{
		printf("builtin function %s in testing mode\n", argv[0]);
		printf("---------------------------------------------\n");
		ft_cd(big, argv);
	}
	else if (argv[0] && !ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		ft_print_pwd(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
		ft_export(big, comm_info);
	else if (argv[0] && !ft_strncmp(argv[0], "unset", ft_strlen(argv[0])))
	{
		ft_unset(big, comm_info);
		//integrate link to unset-function here
	}
	else if (argv[0] && !ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
	{
		ft_print_env(comm_info, big);
	}
	else if (argv[0] && !ft_strncmp(argv[0], "exit", ft_strlen(argv[0])))
	{
		ft_exit_minishell(big, prompt);
	}
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
		&& ((!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
			|| (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
			|| (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
			|| (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
			|| (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])))
			|| (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
			|| (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])))))
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

	curr = big->cmdlist;
	comm_info = curr->content;
	while (curr != NULL)
	{
		comm_info = curr->content;
		if (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
			printf("EXIT WITH ERROR\n");
		else if (ft_builtin_checker(comm_info))
		{
			ft_builtin_executer(comm_info, big, prompt);
			printf("---------------------------------------------\n");
			// return (1);
		}
		else
			ft_test_command_print(prompt, comm_info);
		curr = curr->next;
	}
	ft_free_cl(&(big->cmdlist));
	return (0);
}