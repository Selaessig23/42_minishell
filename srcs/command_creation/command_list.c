/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:45:59 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/14 10:46:02 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the list of commands will be created as part of 
 * t_big big (cmdlist) which will be used in execution part later on
 */

/**
 * @brief this function counts 
 * 1) the total number of commands and writes it to t_big
 * 2) the position (number) of each command
 * 
 * big->exe variable is used for execution of parent type builtins
 * (exit, cd, unset,export). Full execution if `exe` is true, 
 * if `exe` is false - only checking for errors and assigns exit code.
 * 
 * @param command_list the list where each node stands for a command 
 * that has to be counted
 * @param p_big a pointer to the big struct 
 * that holds all information to execute the 
 * commands, here the total amount of commands has to be written in
 */
static void	ft_count_commands(t_list *command_list, t_big **p_big)
{
	t_list	*curr;
	t_big	*big;
	size_t	i;

	curr = command_list;
	big = *p_big;
	i = 0;
	while (curr != NULL)
	{
		big->count_commds += 1;
		i += 1;
		((t_data *)curr->content)->commands_no = i;
		curr = curr->next;
	}
	if (big->count_commds == 1)
		big->exe = true;
	else
		big->exe = false;
}

/**
 * @brief function to create a linked list of commands 
 * (for execution part)
 * which should be part of the struct big (cmdlist)
 * 
 * ft_init_clist in initiate_comm_infos.c
 * 
 * @param lexx the expanded linked list with command line input
 * @param p_big pointer to the struct big to integrate a linked list of
 * commands to (cmdlist)
 */
void	ft_commands(t_list *lexx, t_big **p_big)
{
	t_list	*command_list;
	t_big	*big;

	if (!lexx)
		error_handling(0);
	big = *p_big;
	command_list = NULL;
	((t_lexer *)(lexx->content))->number_helper = 1;
	ft_init_clist(&lexx, &command_list, p_big);
	ft_count_commands(command_list, p_big);
	big->cmdlist = command_list;
}
