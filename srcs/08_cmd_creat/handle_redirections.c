/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:20:28 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/14 10:23:10 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the redirection (operators <<, <, >>, >) 
 * handling is organised
 */

/**
 * @brief function to set values of command struct in case of
 * redirection out (> or >>). If there was set a redirect out before,
 * old fd will be closed and command data will be overwritten.
 * 
 * @param token the specific token (node) of the command line input
 * which stands for the redirection symbol
 * @param comminfo pointer to the struct that holds the command infos
 * @param lexx the expanded linked list with command line input
 * @param p_big pointer to the struct big to integrate the exit code in
 * case of an error when opening redirect out or in
 */
t_list	*ft_set_r_out(t_lexer *token, 
	t_data **cominfo, t_list *lexx, t_big **p_big)
{
	t_data	*comm_info;
	t_big	*big;

	comm_info = *cominfo;
	big = *p_big;
	if (comm_info->fd_outfile > 2)
		close(comm_info->fd_outfile);
	if (token->token == 6)
		comm_info->out_append = true;
	lexx = lexx->next;
	token = lexx->content;
	comm_info->fd_outfile = 
		fd_out_creator(comm_info->out_append, token->value);
	if (comm_info->fd_outfile == -1)
		big->exit_code = 1;
	return (lexx);
}

/**
 * @brief function to set values of command struct in case of
 * redirection in (<) or heredoc-signal (<<). If there was set 
 * a redirect in / heredoc before, old fd will be closed 
 * (and heredoc file will be deleted) and 
 * command data will be overwritten. 
 * 
 * @param token the specific token (node) of the command line input
 * which stands for the redirection symbol
 * @param comminfo pointer to the struct that holds the command infos
 * @param lexx the expanded linked list with command line input 
 * @param p_big pointer to the struct big to integrate the exit code in
 * case of an error when opening redirect out or in
 */
t_list	*ft_set_r_in(t_lexer *token, 
	t_data **cominfo, t_list *lexx, t_big **p_big)
{
	t_data	*comm_info;
	t_big	*big;

	comm_info = *cominfo;
	big = *p_big;
	if (comm_info->fd_infile > 2)
		close(comm_info->fd_infile);
	if (comm_info->in_heredoc == true)
		delete_heredoc(*cominfo);
	if (token->token == 3)
		comm_info->in_heredoc = true;
	lexx = lexx->next;
	token = lexx->content;
	if (token->token == 30)
		comm_info->heredoc_expander = true;
	else
		comm_info->heredoc_expander = false;
	comm_info->fd_infile = 
		fd_in_checker(comm_info, token->value, p_big);
	if (comm_info->fd_infile == -1)
		big->exit_code = 1;
	return (lexx);
}
