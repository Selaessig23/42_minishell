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
void exe_other_builtin(t_data *comm_info, t_big *big) // char *prompt
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
