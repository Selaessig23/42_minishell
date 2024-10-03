#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the help command will be handled
 * this command serves to give general information about
 * the minishell and some instructions on how to use it
 * 
 */

/**
 * @brief 
 */
void	ft_minishell_help(int fd)
{
	ft_putstr_fd("MINISHELL, version 9.9.9.9.0\n", fd);
	// write(1, "\xC2\xA9", (sizeof("\xC2\xA9") - 1));
	// ft_putchar_fd(169, fd);
	ft_putstr_fd("\xC2\xA9 by Maryna Peshko and Markus Stracke\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
	ft_putstr_fd("This shell is written in accordance with 42-subject \"minishell\"\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
	ft_putstr_fd("General instructions:\n", fd);
	ft_putstr_fd("The following operators are not considered (=non-functional):\n", fd);
	ft_putstr_fd("||\n", fd);
	ft_putstr_fd("&&\n", fd);
	ft_putstr_fd("[]\n", fd);
	ft_putstr_fd("{}\n", fd);
	ft_putstr_fd("The shell will not use wildcards.\n", fd);
	ft_putstr_fd("It only considers the following redirctions: <, >, <<, >>\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
}