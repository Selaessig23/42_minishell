/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_comm_infos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:52:23 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/16 03:49:39 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the list of commands will be created as part of 
 * t_big big (cmdlist) which will be used in execution part later on
 */

/**
 * @brief function to set commands_no to
 * the current number and the rest of values 
 * of the command info struct to 0
 * 
 * @param p_comm_info pointer to the struct that 
 * should be set to zero
 * @param lexx to set a commands_no, by default it is
 * set to 1, if there is a pipe it previously increased
 * in function "ft_init_clist"
 */
static void	init_comm(t_data **p_comm_info, t_list *lexx)
{
	t_data	*comm_info;
	t_lexer	*lexx_deref;

	lexx_deref = lexx->content;
	comm_info = *p_comm_info;
	comm_info->cmd = ft_calloc(1, sizeof(char *));
	comm_info->commands_no = (size_t)lexx_deref->number_helper;
	comm_info->in_heredoc = false;
	comm_info->fd_infile = 0;
	comm_info->out_append = false;
	comm_info->fd_outfile = 1;
	comm_info->fd_pipe[0] = -1;
	comm_info->fd_pipe[1] = -1;
	comm_info->id = 0;
}

/**
 * @brief function increase a number of "number_helper"
 * it serves for creation of many heredocs files
 * 
 * @param comm_info is a structure with a current number of
 * command. it is 1, if it was only 1 command before the fisrt
 * occurence of the pipe.
 * @param curr_lexx is a linked list for "t_lexer" type of
 * struct. it containts "number_helper" integer that is used
 * for set a "commands_no" to t_data in each call of "ft_init_clist"
 * function
*/
static void	set_number_helper(t_data *comm_info, t_list *curr_lexx)
{
	int	i;

	i = (int)comm_info->commands_no;
	i++;
	((t_lexer *)(curr_lexx->content))->number_helper = i;
}

/**
 * @brief helper function for ft_init_clist (file command_list.c)
 * that sets the values for all comm_info-struct (uses infos from 
 * cleaned command line input linked list -> lexx)
 * 
 * ft_set_r_in - for input redirection
 * ft_set_r_out - for out redirection
 * by calling these function curr_lexx will be updated 
 * (= return value of these functions)
 * 
 * @param p_node_content a pointer to the content of the current node of 
 * the (cleaned and expanded) linked list of command line input
 * @param p_comm_info a pointer to the current content of the 
 * linked list of commands (for execution)
 * @param p_curr_lexx a pointer to the current node of 
 * the (cleaned and expanded) linked list of command line input
 * @param p_big pointer to the struct big to integrate the exit code in
 * case of an error when opening redirect out or in
 */
static void	ft_set_comminfo_values(t_lexer **p_node_content, 
	t_data **p_comm_info, t_list **p_curr_lexx, t_big **p_big)
{
	t_lexer	*node_content;
	t_data	*comm_info;
	t_list	*curr_lexx;

	node_content = *p_node_content;
	comm_info = *p_comm_info;
	curr_lexx = *p_curr_lexx;
	if (node_content->token == 3 || node_content->token == 4)
		curr_lexx = ft_set_r_in(node_content, &comm_info, curr_lexx, p_big);
	else if (node_content->token == 5 || node_content->token == 6)
		curr_lexx = ft_set_r_out(node_content, &comm_info, curr_lexx, p_big);
	else
		if (*node_content->value)
			ft_add_arr_end(node_content->value, &comm_info);
	*p_curr_lexx = curr_lexx;
}

/**
 * @brief helper function for ft_init_clist (file command_list.c)
 * that iterates to next node of the linked list of command line input
 * in certain cases
 * 
 * if we want to consider ";" it is already integrated:
 * 	while (curr_lexx != NULL 
 * 		&& (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0) 
 * 		&& node_content->token != 1 && node_content->token != 2)
 *   (token 2 == ";")
 * 
 * @param p_curr_lexx a pointer to the current node of 
 * the (cleaned and expanded) linked list of command line input
 * @param p_node_content a pointer to the content of the current node of 
 * the (cleaned and expanded) linked list of command line input
 * @param p_comm_info a pointer to the current content of the 
 * linked list of commands (for execution)
 */
static void	ft_update_node(t_list **p_curr_lexx, t_lexer **p_node_content, 
	t_data **p_comm_info)
{
	t_data	*comm_info;
	t_list	*curr_lexx;
	t_lexer	*node_content;

	comm_info = *p_comm_info;
	curr_lexx = *p_curr_lexx;
	node_content = *p_node_content;
	if (curr_lexx != NULL)
		curr_lexx = curr_lexx->next;
	if (curr_lexx != NULL)
		node_content = curr_lexx->content;
	while (curr_lexx != NULL
		&& (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
		&& node_content->token != 1 && node_content->token != 2)
	{
		curr_lexx = curr_lexx->next;
		if (curr_lexx != NULL)
			node_content = curr_lexx->content;
	}
	*p_curr_lexx = curr_lexx;
	*p_node_content = node_content;
}

/**
 * @brief this function initiate the linked list of commands by
 * checking the tokens of the command line input, opening all fds
 * and creating heredoc.
 * 
 * variable "number_helper" helps to create many heredocs
 * 
 * if we want to consider ";" it is already integrated:
 * 	if (node_content->token == 1 || node_content->token == 2)
 * (token 2 == ";")
 * 
 * @param lexx the expanded linked list with command line input 
 * @param command_list linked list of commands which should be filled
 * with command information for each command (each sommand = node)
 * @param p_big pointer to the struct big to integrate the exit code in
 * case of an error when opening redirect out or in
 */
void	ft_init_clist(t_list **lexx, t_list **command_list, t_big **p_big)
{
	t_data	*comm_info;
	t_list	*curr_lexx;
	t_lexer	*node_content;

	comm_info = NULL;
	curr_lexx = *lexx;
	node_content = curr_lexx->content;
	comm_info = ft_calloc(1, sizeof(t_data));
	if (!comm_info)
		error_handling(2);
	init_comm(&comm_info, *lexx);
	while (curr_lexx != NULL && node_content->token != 1 
		&& node_content->token != 2)
	{
		ft_set_comminfo_values(&node_content, &comm_info, &curr_lexx, p_big);
		ft_update_node(&curr_lexx, &node_content, &comm_info);
	}
	ft_lstadd_back(command_list, ft_lstnew(comm_info));
	if (node_content->token == 1 || node_content->token == 2)
	{
		curr_lexx = curr_lexx->next;
		set_number_helper(comm_info, curr_lexx);
		ft_init_clist(&curr_lexx, command_list, p_big);
	}
}
