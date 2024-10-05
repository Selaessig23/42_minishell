#include "minishell.h"

/**
 * @brief This function displays an error message when the specified
 * output file cannot be found or opened.
 * 
 * @param outfile: The name of the output file that could not be found.
 */
static void	error_file(char *outfile)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(outfile, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * @brief This function displays an error message when there is a permission
 * issue while trying to access or open a file.
 * 
 * @param name_file: The name of the file that lacks the necessary
 * permissions.
 */
static void	error_permission(char *name_file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name_file, STDERR_FILENO);
	ft_putstr_fd(": Permission denied", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * @brief This function attempts to open the specified output file
 * for writing. If the file cannot be opened due to permission issues
 * or other errors, it displays appropriate error messages.
 */
static int	open_outfile(char *name_file)
{
	int	file_out;

	file_out = 0;
	file_out = open(name_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(name_file, W_OK) != 0)
	{
		error_permission(name_file);
		return(-1);
	}
	if (file_out == -1)
	{
		error_file(name_file);
		return(-1);
	}
	return (file_out);
}

/**
 * @brief Reads user input from the terminal and writes it to the file
 * until the limiter string is entered.
 * 
 * This function enters an infinite loop, prompting the user with "> "
 * to enter input. It reads lines using get_next_line(0)
 * (from standard input), and checks if the line matches the limiter.
 * The condition 'str[ft_strlen(lim)] == 10' checks whether the next
 * character after the word LIMITER is '\n' which is 10 in ASCII.
 * 
 * @param write_end: File descriptor for the file being written to.
 * @param lim: The delimiter string that marks the end of the input.
 */
static void	here_read_helper(int write_end, char *lim)
{
	char	*str;

	while (1)
	{
		write(1, ">", 1);
		write(1, " ", 1);
		str = get_next_line(0);
		if (ft_strncmp(str, lim, ft_strlen(lim)) == 0
			&& str[ft_strlen(lim)] == 10)
		{
			free(str);
            return ;
		}
		write(write_end, str, ft_strlen(str));
		free(str);
	}
}

/**
 * @brief Opens a file and reads from standard input until
 * a limiter is encountered. It passes the file descriptor "fd"
 * and the limiter to "here_read_helper(), which performs the
 * actual reading of input and writes it to the file.
 * 
 * @param name: Name of the file to open for writing.
 * @param lim: The delimiter string that marks the end of the input.
 */
static int	here_read(char *name, char *lim)
{
	int     fd;

    fd = open_outfile(name);
	here_read_helper(fd, lim);
	return (fd);
}

/**
 * @brief This function starts the "heredoc" process, which takes input
 * from the terminal until a specific limiter string is encountered.
 * This function generates a filename based on the number of commands
 * (from comm_info->commands_no), represented as .heredoc_X, where X
 * is a unique identifier.
 * 
 * @param comm_info: The pointer to a structure containing command
 * information (stores the number of commands, "commands_no").
 * @param limiter: The string that serves as the stopping point for input.
 */
int heredoc_start(t_data *comm_info, char *limiter)
{
    int     fd;
    char    *name;
	char    *cmd_no_str;
    
    cmd_no_str = ft_itoa(comm_info->commands_no);
    name = ft_strjoin(".heredoc_", cmd_no_str);
    free(cmd_no_str);
    fd = here_read(name, limiter);
    free(name);
    return (fd);
}
