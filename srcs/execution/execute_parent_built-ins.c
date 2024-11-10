#include "minishell.h"

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