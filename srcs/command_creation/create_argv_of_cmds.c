/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv_of_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:54:04 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/14 10:54:39 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the list of commands will be created as part of 
 * t_big big (cmdlist) which will be used in execution part later on
 */

/**
 * @brief (helper) function (for to ft_add_arr_back) to add existing 
 * strings from command_array_old to command_array_new
 * 
 * @param p_old pointer to the old command array (to copy from)
 * @param p_new pointer to the new command array (to copy to)
 */
static int	ft_arrcpy(char ***p_old, char ***p_new)
{
	int		i;
	char	**old;
	char	**new;

	i = 0;
	if (*p_old == NULL)
		return (0);
	old = *p_old;
	new = *p_new;
	while (old[i] != NULL)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	return (i);
}

/**
 * @brief function to create an array of commands (**cmd) which 
 * will serve as argv in execution part, it adds a new string
 * to the array of strings at the end
 * 
 * @param token_value the value of the specific token (node) of the 
 * command line input that has to be added to **cmd
 * @param p_comm_info pointer to the struct of command information
 */
void	ft_add_arr_end(char *token_value, t_data **p_comm_info)
{
	t_data	*comm_info;
	char	**command_array_old;
	char	**command_array_new;
	size_t	count;
	size_t	i;

	i = 0;
	comm_info = *p_comm_info;
	command_array_old = comm_info->cmd;
	count = ft_arrlen(command_array_old);
	command_array_new = (char **)malloc(sizeof(char *) * (count + 2));
	if (!command_array_new)
		error_handling(2);
	if (count > 0)
		i += ft_arrcpy(&command_array_old, &command_array_new);
	command_array_new[i] = ft_strdup(token_value);
	if (!command_array_new[i])
		error_handling(2);
	i += 1;
	command_array_new[i] = NULL;
	comm_info->cmd = command_array_new;
	if ((command_array_old))
		ft_free(command_array_old);
}
