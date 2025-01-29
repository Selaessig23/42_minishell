/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:43:57 by mstracke          #+#    #+#             */
/*   Updated: 2025/01/29 15:33:02 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION
 * in this file the incrementation of 
 * env-variable $SHLVL in case of executing minishell
 * within a minishell-environment is handled
 */

/**
 * @brief function to convert existing SHLVL-value (char) into a number (int)
 * 
 * @param shlvl_old 
 */
int	ft_shlvl_converter(char *shlvl_old)
{
	int	i;

	i = 0;
	while (shlvl_old[i])
	{
		if (!ft_isdigit(shlvl_old[i]) && shlvl_old[i] != '-'
			&& shlvl_old[i] != '+')
			return (0);
		i += 1;
	}
	return (ft_atoi(shlvl_old));
}

/**
 * @brief function that organises the increasement of env-variable
 * SHLVL (SHELL-LEVEL) in case of executing ./minishell
 * within minishell
 * 
 * @param env an array of strings with all environmental variables
 */
void	ft_ms_executer(char *env[])
{
	char	*temp;
	char	*shlvl_new;
	char	*count_new;
	int		count;

	count = 0;
	while (*env && ft_strncmp("SHLVL", *env, 4))
		env++;
	temp = *env;
	count = ft_shlvl_converter(temp + 6);
	if (count < 0)
		count = 0;
	else 
		count += 1;
	count_new = ft_itoa(count);
	if (!count_new)
		error_and_exit(1);
	shlvl_new = ft_strjoin("SHLVL=", count_new);
	if (!shlvl_new)
		error_and_exit(1);
	free(count_new);
	*env = shlvl_new;
	free (temp);
}

/**
 * Function checks if the command cmd is exactly "./minishell".
 * If so, it executes the `ft_ms_executer` function.
 * 
 * If the command is not "./minishell", it simply returns 1.
 * 
 * The condition cmd[ft_strlen("./minishell")] == '\0' checks if the string 
 * cmd has exactly the content ./minishell, with no additional characters 
 * after it.
 */
int	is_minishell_command(char *cmd, char *env[])
{
	if (!ft_strncmp(cmd, "./minishell", ft_strlen("./minishell"))
		&& cmd[ft_strlen("./minishell")] == '\0')
	{
		ft_ms_executer(env);
		return (0);
	}
	else
		return (1);
}
