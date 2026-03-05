/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:05:17 by mstracke          #+#    #+#             */
/*   Updated: 2026/03/05 16:36:24 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This will make ECHOCTL available and silence VSCode's warning.
#define _DEFAULT_SOURCE	// is the modern way to enable BSD and SVID features 
						// (including ECHOCTL)
#define _BSD_SOURCE		// is the older way, kept for compatibility

#include "minishell.h"
#include <termios.h>

/**
 * DESCRIPTION
 * in this file the creation of heredoc files is organised.
 */
/**
 * @brief function to expand the heredoc file with env-var infos
 * 
 * @param str a pointer to the string that should be expanded
 * @param p_big a pointer to the big struct 
 * that holds all information to execute the 
 * commands, here the env to expand heredoc in case it should be expandable
 */
static void	ft_expand_heredoc(char **str, t_big **p_big)
{
	t_lexer	*heredoc_input;
	char	*temp;

	temp = *str;
	heredoc_input = ft_calloc(1, sizeof(t_lexer));
	heredoc_input->value = temp;
	heredoc_input->token = 20;
	heredoc_input->number_helper = 0;
	ft_var_checker((void **)&heredoc_input, *p_big);
	*str = heredoc_input->value;
	free(heredoc_input);
}

/**
 * The function deletes a tmp file of heredoc
 * in case there are two or more heredocs in
 * one command.
 * For instance, "<< LIM << LIM << LIM"
 * 
 * @param comm_info A pointer to a structure containing command
 * information (stores the number of commands, "commands_no",
 * required to built the name of the heredoc-file).
 */
void	delete_heredoc(t_data *comm_info)
{
	char	*pathname;
	char	*cmd_no_str;

	cmd_no_str = ft_itoa(comm_info->commands_no);
	pathname = ft_strjoin("/tmp/heredoc_", cmd_no_str);
	free(cmd_no_str);
	unlink(pathname);
	free(pathname);
}

/**
 * @brief function that returns an error message in case of
 * readline input is empty (CRTL+D)
 * 
 * @param lim The delimiter string that marks the end of the input.
 */
int	ft_heredoc_error(char *lim)
{
	ft_putstr_fd("bash: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("\')\n", 2);
	return (0);
}

/**
 * @brief Reads input for a heredoc until a delimiter is found or a
 * signal (CTRL+C) is received.
 *
 * This function sets the signal handler for heredoc mode 
 * (`ft_handle_signals(true)`). It then enters a loop, reading lines using 
 * `get_next_line`.  * The loop terminates if the input line matches 
 * the delimiter (`lim`) or if the global `g_signalnum` is set to 1 by 
 * a SIGINT signal.
 * If CTRL+D is pressed (`get_next_line` returns NULL), it prints a warning.
 *
 * @param write_end File descriptor for the file being written to
 * @param lim The delimiter string that marks the end of the input
 * @param p_big a pointer to the big struct that holds all info to execute 
 * the commands, here the env to expand heredoc in case it should be expandable
 * @param  comm_info A pointer to a structure containing command
 * information (stores the info if heredoc should be expandable).
 */
static int	here_read_helper(int write_end, char *lim,
	t_big **p_big, t_data *comm_info)
{
	char	*str;
	struct termios	term;
    struct termios	term_orig;

	str = NULL;
	ft_handle_signals(true);
	// Disable echoing of SIGQUIT (CTRL+\)
    tcgetattr(STDIN_FILENO, &term_orig);
	term = term_orig;
	// ECHOCTL is a flag that controls whether control chars (CTRL+) are echoed
	term.c_lflag &= ~ECHOCTL;  // Disable control character echoing
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (g_signalnum != 1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!str && g_signalnum != 1)
			return (ft_heredoc_error(lim));
		if (str && ft_strncmp(str, lim, ft_strlen(lim)) == 0
			&& str[ft_strlen(lim)] == 10)
		{
			free(str);
			return (0);
		}
		if (str)
		{
			if (comm_info->heredoc_expander == true)
				ft_expand_heredoc(&str, p_big);
			write(write_end, str, ft_strlen(str));
			ft_putchar_fd('\n', write_end);
			free(str);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
	if (g_signalnum == 1)
        return (1);
	return (0);
}

/**
 * @brief This function starts the "heredoc" process, which takes input
 * from the terminal until a specific limiter string is encountered.
 * This function generates a filename based on the number of commands
 * (from comm_info->commands_no), represented as .heredoc_X, where X
 * is a unique identifier.
 *
 * @param comm_info The pointer to a structure containing command
 * information (stores the number of commands, "commands_no").
 * @param limiter The string that serves as the stopping point for input.
 * @param p_big a pointer to the big struct 
 * that holds all information to execute the 
 * commands, here the env to expand heredoc in case it should be expandable
 */
int	heredoc_start(t_data *comm_info, char *limiter, t_big **p_big)
{
	int		fd;
	char	*name;
	char	*cmd_no_str;

	cmd_no_str = ft_itoa(comm_info->commands_no);
	name = ft_strjoin("/tmp/heredoc_", cmd_no_str);
	free(cmd_no_str);
	fd = fd_here_creator(name, true);
	here_read_helper(fd, limiter, p_big, comm_info);
	close(fd);
	if (g_signalnum != 1)
		fd = fd_here_creator(name, false);
	else
	{
		unlink(name);
		fd = -1;
	}
	free(name);
	name = NULL;
	return (fd);
}
