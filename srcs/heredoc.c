#include "minishell.h"

void	error_file(char *outfile)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(outfile, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	error_permission(char *name_file)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(name_file, STDERR_FILENO);
	ft_putstr_fd(": Permission denied", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static int	open_outfile(char *name_file)
{
	int	file_out;

	file_out = 0;
	file_out = open(name_file, O_WRONLY | O_TRUNC | O_CREAT, 0644); // O_APPEND
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
 * The function to read from STANDARD INPUT for heredoc.
 * 
 * The condition 'str[ft_strlen(lim)] == 10' checks whether the next
 * character after the word LIMITER is '\n' which is 10 in ASCII.
 */
static void	here_read_helper(int write_end, char *lim)
{
	char	*str;

	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(str, lim, ft_strlen(lim)) == 0
			&& str[ft_strlen(lim)] == 10)
		{
			free(str);
			//exit(EXIT_SUCCESS);
            return ;
		}
		write(write_end, str, ft_strlen(str));
		free(str);
	}
}

static int	here_read(char *name, char *lim)
{
	//int		pip;
	//int		id;
	//int		fd[2];
    int     fd;

    fd = open_outfile(name);
	//pip = pipe(fd);
	//id = fork();
	//if (id == 0)
	//{
		//close(fd[0]);
		//here_read_helper(fd[1], lim);
		//here_read_helper(fd, lim);
	//}
	here_read_helper(fd, lim);
	//close(fd[1]);
	//waitpid(id, NULL, 0);
	return (fd);
}

// The function reads from the standart input with get_next_line
// and writes to the ...... 
// TO DESCRIBE
int heredoc_start(t_data *comm_info, char *limiter)
{
    int     fd;
    char    name[100] = ".heredoc_0";
    int     code;
    char    c;

    code = (int)((comm_info->commands_no));
    c = (char)(code + '@');
    name[9] = c;
    printf("name string: %s\n", name);
    fd = here_read(name, limiter);
    return (fd);
}
