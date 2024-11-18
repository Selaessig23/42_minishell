/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:30:24 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/18 15:41:33 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * file which holds all functions of directory command_creation
 * that are required by more than one file of functions
 */

void	exe_fd_error(t_big *big, t_data *comm_info_next)
{
	big->exit_code = 1;
	if (comm_info_next && comm_info_next->fd_infile == 0)
		comm_info_next->fd_infile = open("/dev/null", O_RDONLY);
}

t_data	*ft_pointer_next_command(t_list	*curr)
{
	if (curr->next != NULL)
		return (curr->next->content);
	else
		return (NULL);
}

/**
 * @brief function to free the linked list of commands
 * 
 * @param ll the linked list to free
 */
void	ft_free_cl(t_list **ll)
{
	t_list	*temp;
	t_list	*curr;
	t_data	*comm_info;

	if (*ll != NULL)
		curr = *ll;
	else
	{
		temp = NULL;
		curr = NULL;
		comm_info = NULL;
	}
	while (curr != NULL)
	{
		temp = curr;
		comm_info = temp->content;
		curr = curr->next;
		ft_free(comm_info->cmd);
		free(comm_info);
		free(temp);
		temp = NULL;
	}
	*ll = NULL;
}
