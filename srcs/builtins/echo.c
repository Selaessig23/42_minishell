#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the inbuilt-function "echo"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to get the fd of the outfile
 * 
 * MAYBE REWRITE FOR GENERAL USAGE OF EXECUTION PART
 * IMPROVE AND CHECKE !!! (WAS JUST COPIED FROM PIPEX)
 * 
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
// static int	ft_get_fd(t_data *comm_info)
// {
// 	int	fd_out;

// 	fd_out = 0;
// 	if (access(comm_info->outfile, F_OK))
// 	{
// 		fd_out = open(comm_info->outfile, O_CREAT, 0644);
// 		if (fd_out == -1)
// 			error_handling(1);
// 	}
// 	else if (!access(comm_info->outfile, W_OK))
// 	{
// 		fd_out = open(comm_info->outfile, O_TRUNC);
// 		if (fd_out == -1)
// 			error_handling(1);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("zsh: ", 2);
// 		ft_printf("permission denied: %s\n", comm_info->outfile);
// 		return (-1);
// 	}
// 	close(fd_out);
// 	return (0);
// }


/**
 * function to print a string
 * 
 * TODO: set exit status in struct big after execution
 * TODO: CONSIDER >> append
 *
 * @param comm_info struct with all necessary infos to 
 * execute a single command 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env
 */
void    ft_echo(t_data *comm_info)
{
    char	**argv;
	int		fd;
    bool    no_nl;

	argv = comm_info->cmd;
    no_nl = 0;
    fd = comm_info->fd_outfile;
	// if (comm_info->outfile)
	// {
	// 	fd = ft_get_fd(comm_info);
	// 	if (fd == -1)
	// 	{
	// 		big->exit_code = 1;
	// 		// return (1);
	// 	}
	// }
    while (*argv)
    {
        if (!ft_strncmp(*argv, "echo", ft_strlen(*argv)))
            argv += 1;
        else if (!ft_strncmp(*argv, "-n", ft_strlen(*argv)))
        {
            no_nl = true;
            argv += 1;
        }
        else
        {
            ft_putstr_fd(*argv, fd);
            argv += 1;
        }
    }
    if (no_nl == 0)
        ft_putchar_fd('\n', fd);
}
