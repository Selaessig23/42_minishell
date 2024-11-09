#include "minishell.h"

// Check if it is parent type built-ins
// Parent type built-ins are built-ins that fully executable
// only when it is only one command that executes without
// forking.
int checker_parent_builtin(t_data *comm_info)
{
	char **argv;

	argv = comm_info->cmd;
	if (argv[0] != NULL)
	{
		if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("cd"))
			return (1);
		if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("export"))
			return (1);
		if (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("unset"))
			return (1);
		if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("exit"))
			return (1);
		if (!ft_strncmp(argv[0], "help", ft_strlen(argv[0])) && ft_strlen(argv[0]) == ft_strlen("help"))
			return (1);
	}
	return (0);
}

// export, unset, cd, exit
// execution IF exe is true
// if exe is false - checking for errors and exit assigns exit code
void parent_builtin_exe(t_data *comm_info, t_big *big, char *prompt)
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