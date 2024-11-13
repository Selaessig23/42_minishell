/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:43:57 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/13 15:44:17 by mstracke         ###   ########.fr       */
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
		error_handling(1);
	shlvl_new = ft_strjoin("SHLVL=", count_new);
	if (!shlvl_new)
		error_handling(1);
	free(count_new);
	*env = shlvl_new;
	free (temp);
}
