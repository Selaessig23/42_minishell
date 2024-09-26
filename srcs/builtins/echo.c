#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the inbuilt-function "echo"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * function to print a string
 * 
 * TODO: set exit correct (when 1?) status in struct big after execution
 *
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 * @param big big struct with all command infos, inclusive
 * env and exit status
 */
void    ft_echo(t_data *comm_info, t_big *big)
{
	char	**argv;
	int		fd;
	bool	no_nl;

	argv = comm_info->cmd;
	no_nl = 0;
	fd = comm_info->fd_outfile;
	argv += 1;
	if (*argv && !(ft_strncmp(*argv, "-n", ft_strlen(*argv))))
	{
		no_nl = true;
		argv += 1;
	}
	// printf("fd-check: %i\n", fd);
	while (*argv)
	{
		ft_putstr_fd(*argv, fd);
		// printf("to print -check: %s\n",*argv);
		// dprintf(fd, "print: %s", *argv);
		argv += 1;
		if (*argv)
			ft_putchar_fd(' ', fd);
	}
	// printf("fd-check 2: %i\n", fd);
	if (no_nl == 0)
		ft_putchar_fd('\n', fd);
	if (fd > 2)
		close(fd);
	big->exit_code = 0;
}
