#include "minishell.h"

/**
 * DESCRIPTION: 
 * in this file the inbuilt-function "pwd"
 * which should work similar to the bash-function
 * of same name is created
 */

/**
 * @brief function to get and print current working directory
 * if there is no variable for it in env
 * 
 * @param fd the file descriptor to write in
 */
static void	ft_get_env_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		error_handling(2);
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
}

/**
 * @brief function to print content of env-variable 'pwd'
 * 
 * TODO: set exit correct (when 1?) status in struct big after execution
 * 
 * @param big the struct which holds all information for 
 * execution part incl. cmdlist and env and exit status
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
void	ft_print_pwd(t_big *big, t_data *comm_info)
{
	char	**envp;
	int		fd;

	envp = big->env;
	fd = comm_info->fd_outfile;
	// while (*envp && ft_strncmp("PWD=", *envp, 4))
	// 	envp++;
	// if (*envp == NULL || ft_strncmp("PWD=", *envp, 4))
		ft_get_env_pwd(fd);
	// else
	// {
	// 	ft_putstr_fd(*envp + 4, fd);
	// 	ft_putchar_fd('\n', fd);
	// }
	if (fd > 2)
		close(fd);
	big->exit_code = 0;
	// return (0);
}
