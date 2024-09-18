#include "minishell.h"

/**
 * DESCRIPTION: 
 * in this file the inbuilt-function "pwd"
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
int	ft_get_fd(t_data *comm_info)
{
	int	fd_out;

	fd_out = 0;
	if (access(comm_info->outfile, F_OK))
	{
		fd_out = open(comm_info->outfile, O_CREAT, 0644);
		if (fd_out == -1)
			error_handling(1);
	}
	else if (!access(comm_info->outfile, W_OK))
	{
		fd_out = open(comm_info->outfile, O_TRUNC);
		if (fd_out == -1)
			error_handling(1);
	}
	else
	{
		ft_putstr_fd("zsh: ", 2);
		ft_printf("permission denied: %s\n", comm_info->outfile);
		return (-1);
	}
	close(fd_out);
	return (0);
}

/**
 * @brief function to print content of env-variable 'pwd'
 * to outfile or STDOUT if outfile = NULL
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
void	ft_print_pwd(t_big *big, t_data *comm_info)
{
	char	**envp;
	int		fd;

	envp = big->env;
	fd = 0;
	if (comm_info->outfile)
	{
		fd = ft_get_fd(comm_info);
		if (fd == -1)
		{
			big->exit_code = 1;
			// return (1);
		}
	}
	while (*envp && ft_strncmp("PWD=", *envp, 4))
		envp++;
	ft_putstr_fd(*envp + 4, fd);
	ft_putchar_fd('\n', fd);
	// return (0);
}
