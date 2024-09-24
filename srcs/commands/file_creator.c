#include "minishell.h"

/**
 * DESRIPTION: 
 * file to check accessibility if files, creates heredocs if asked for and 
 * and in case of output redirect also create the files that are asked for in 
 * command line input
 */


/**
 * checks if infile is accessible and opens it. Initiate heredoc if required.
 * 
 * @param heredoc to check if a new heredoc file has to be created
 * @param infile the infile name to read from
 */
int	fd_in_checker(bool heredoc, char *infile)
{
	int		fd_in;

	fd_in = 0;
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
		fd_in = open(infile, O_RDONLY);
	return (fd_in);
}

/**
 * @brief function to get the fd of the outfile and check 
 * accessibility
 * 
 * @param appender information if filename should be opened with trunc-mode
 * or append-mode (true)
 * @param filename filename (outfile) to write in 
 */
static int	ft_get_fd(bool appender, char *filename)
{
	int	fd_out;

	fd_out = 0;
	if (!access(filename, W_OK) && appender == true)
	{
		fd_out = open(filename, O_WRONLY | O_APPEND);
		if (fd_out == -1)
			error_handling(1);
	}
	else if (!access(filename, W_OK))
	{
		fd_out = open(filename, O_WRONLY | O_TRUNC);
		if (fd_out == -1)
			error_handling(1);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_printf("%s: Permission denied\n", filename);
		return (-1);
	}
	return (fd_out);
}

/**
 * function to check if outfile exists. If not it will be created. 
 * If yes, function ft_get_fd will check accessibility
 * 
 * @param appender information if filename should be opened with trunc-mode
 * or append-mode (true)
 * @param filename filename (outfile) to write in 
 */
int	fd_out_creator(bool appender, char *filename)
{
	int		fd_out;

	fd_out = 0;
	if (access(filename, F_OK))
	{
		fd_out = open(filename, O_CREAT, 0644);
		if (fd_out == -1)
			error_handling(1);
	}
	else
		fd_out = ft_get_fd(appender, filename);
	return (fd_out);
}