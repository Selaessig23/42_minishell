/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:25:29 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 20:13:44 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_welcome_help(int fd)
{
	ft_putstr_fd("MINISHELL, version 9.9.9.9.0\n", fd);
	ft_putstr_fd("\xC2\xA9 by Maryna Peshko and Markus Stracke\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
	ft_putstr_fd("This shell is written in accordance ", fd);
	ft_putstr_fd("with 42-subject \"minishell\"\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
	ft_putstr_fd("General instructions:\n", fd);
	ft_putstr_fd("The following operators are not ", fd);
	ft_putstr_fd("considered (=non-functional):\n", fd);
	ft_putstr_fd("||\n", fd);
	ft_putstr_fd("&&\n", fd);
	ft_putstr_fd("[]\n", fd);
	ft_putstr_fd("{}\n", fd);
	ft_putstr_fd("The shell will not use wildcards.\n", fd);
	ft_putstr_fd("It only considers the following ", fd);
	ft_putstr_fd("redirctions: <, >, <<, >>\n", fd);
	ft_putstr_fd("-------------------------------------------\n", fd);
}

void	ft_welcome(void)
{
	int	fd;

	fd = 1;
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("            _         _       _            _  _\n", fd);
	ft_putstr_fd("	   (_)       (_)     | |          | || |\n", fd);
	ft_putstr_fd("_ __ ___    _  _ __   _  ___ | |__    ___ | || |\n", fd);
	ft_putstr_fd("| '_ ` _ \\ | || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n", fd);
	ft_putstr_fd("| | | | | || || | | || |\\__ \\| | | ||  __/| || |\n", fd);
	ft_putstr_fd("|_| |_| |_||_||_| |_||_||___/|_| |_| \\___||_||_|\n", fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("\n", fd);
	ft_welcome_help(fd);
	ft_putstr_fd("HAVE FUN USING IT!!!\n\n", fd);
}

/**
 * @brief checks for empty input (only tabs or spaces)
 * to ignore it in history and return a new prompt
 * 
 * @param input the readline input
 */
int	ft_spacetabchecker(char *input)
{
	while (*input)
	{
		if ((*input >= 9 && *input <= 11)
			|| *input == 32)
			input += 1;
		else
			return (0);
	}
	return (1);
}

/**
 * The function copies array of strings from environmental 
 * variables into array of strings that is a part of
 * struct t_big.
*/
char	**copy_envp(char **envp)
{
	char	**copy;
	int		i;
	int		j;
	int		str_size;

	j = 0;
	i = count_strings(envp);
	str_size = 0;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (!copy)
		error_and_exit(2);
	while (envp[j])
	{
		str_size = ft_strlen(envp[j]) + 1;
		copy[j] = ft_calloc(str_size, sizeof(char));
		if (!copy[j])
			error_and_exit(2);
		copy[j] = ft_memcpy(copy[j], envp[j], str_size);
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

/**
 * Function initialize t_big struct and copies the environmental
 * varibles into array of strings char **env.
 * 
 * @param t_big	*big
 * @param char **envp
 * @param char	**env
 * 
 * by default big->exe = true;
*/
t_big	*init_t_big(char **envp)
{
	t_big	*big;
	char	**env;
	char	*all_folders;

	big = ft_calloc(1, sizeof(t_big));
	if (big == NULL)
		error_and_exit(2);
	big->cmdlist = NULL;
	env = copy_envp(envp);
	big->env = env;
	all_folders = get_all_folders("PATH", env);
	big->binarypaths = ft_split(all_folders, ':');
	if (!big->binarypaths)
	{
		perror("malloc");
		return (NULL);
	}
	big->exit_code = 0;
	big->count_commds = 0;
	big->exe = true;
	return (big);
}
