#include "minishell.h"
#include <sys/ioctl.h>

/**
 * The function deletes a tmp file of heredoc
 * in case there are two or more heredocs in
 * one command.
 * For instance, "<< LIM << LIM << LIM"
*/
void	delete_heredoc(t_data *comm_info)
{
	char	*pathname;
	char	*cmd_no_str;

	cmd_no_str = ft_itoa(comm_info->commands_no);
	pathname = ft_strjoin(".heredoc_", cmd_no_str);
	free(cmd_no_str);
	unlink(pathname);
	free(pathname);
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
static int	here_read_helper(int write_end, char *lim)
{
	char	*str;

	str = NULL;
	while (signalnum != 3)
	{
		// printf("signalnum A: %i\n", signalnum);
		// printf("signalnum B: %i\n", signalnum);
		ft_putstr_fd("> ", 1);
		ft_handle_signals(false);
		str = get_next_line(0);
		if (!str && signalnum != 3)
		{
			ft_putstr_fd("bash: warning: here-document at line 1 ", 2);
			ft_putstr_fd("delimited by \"end-of-file (wanted `", 2);
			ft_putstr_fd(lim, 2);
			ft_putstr_fd("\')\n", 2);
			signalnum = 3;
		}
		// dprintf(2, "print str: $%s$, count str: %zu\n", str, ft_strlen(str));
		if (str && ft_strncmp(str, lim, ft_strlen(lim)) == 0
			&& str[ft_strlen(lim)] == 10)
		// if (str && ft_strncmp(str, lim, ft_strlen(lim)) == 0
		// 	&& ft_strlen(lim) == ft_strlen(str))
		{
			free(str);
			return (0);
		}
		if (str)
		{
			write(write_end, str, ft_strlen(str));
			free(str);
		}
	}
	if (signalnum == 3)
	{
		signalnum = 0;
		return (1);
	}
	return (0);
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
	int	fd;

	(void) lim;
	fd = fd_out_creator(false, name);
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
int	heredoc_start(t_data *comm_info, char *limiter)
{
	int		fd;
	char	*name;
	char	*cmd_no_str;

	cmd_no_str = ft_itoa(comm_info->commands_no);
	name = ft_strjoin(".heredoc_", cmd_no_str);
	free(cmd_no_str);
	fd = here_read(name, limiter);
	free(name);
	if (here_read_helper(fd, limiter))
		fd = -1;
	return (fd);
}
