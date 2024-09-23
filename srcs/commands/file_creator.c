#include "minishell.h"

/**
 * DESRIPTION: 
 * file to check and in case of output redirect
 * also create the files that are asked for in 
 * command line input
 */


/**
 * checks if infile is accessible and initiate heredoc if required,
 * closes old file if exist
 * 
 * @param infos the struct with all required variables
 * @param infile the infile path or document
*/
int	fd_in_checker(bool heredoc_old, int fd_old, bool heredoc, char *infile)
{
	int		fd_in;

	fd_in = 0;
	if (fd_old)
		close(fd_old);
	if (heredoc_old == true)
	{
		//delete old temp file of heredoc here?
		printf("heredoc temp file has to be deleted\n");
	}
	if (heredoc == true)
	{
		//integrate heredoc here?
		printf("function to call heredoc\n");
	}
	else if (access(infile, F_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_printf("%s: no such file or directory\n", infile);
		fd_in = -1;
	}
	else if (access(infile, R_OK))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_printf("%s: Permission denied\n", infile);
		fd_in = -1;
	}
	else
		fd_in = open(infile, R_OK);
	return (fd_in);
}

/**
 * @brief function to get the fd of the outfile
 * 
 * MAYBE REWRITE FOR GENERAL USAGE OF EXECUTION PART
 * IMPROVE AND CHECKE !!! (WAS JUST COPIED FROM PIPEX)
 * 
 * @param comm_info struct with all necessary infos to 
 * execute a single command
 */
static int	ft_get_fd(bool appender, char *filename)
{
	int	fd_out;

	fd_out = 0;
	if (!access(filename, W_OK) && appender == true)
	{
		fd_out = open(filename, O_APPEND);
		if (fd_out == -1)
			error_handling(1);
	}
	else if (!access(filename, W_OK))
	{
		fd_out = open(filename, O_TRUNC);
		if (fd_out == -1)
			error_handling(1);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_printf("%s: Permission denied\n", filename);
		return (-1);
	}
	close(fd_out);
	return (0);
}

/**
 * 
 */
int	fd_out_creator(int fd_old, bool appender, char *filename)
{
	int		fd_out;

	fd_out = 0;
	if (fd_old)
		close(fd_old);
	if (access(filename, F_OK))
	{
		fd_out = open(filename, O_CREAT, 0644);
		if (fd_out == -1)
			error_handling(1);
	}
	else
		fd_out = ft_get_fd (appender, filename);
	return (fd_out);
}