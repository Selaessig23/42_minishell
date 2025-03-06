/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:17:15 by mstracke          #+#    #+#             */
/*   Updated: 2025/03/06 10:51:33 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief this function organises the parsing part
 * (the preparation of command line input for execution)
 * 1st an array of strings (input_arr) is created out of 
 * the readline input (all keywords are seperated here)
 * (create_cleanarr)
 * 2nd the array of strings is trasnformed into a
 * linked list and each node get a token describing
 * the type of the input-keyword (=ft_tokenizer)
 * 3rd check for syntax errors (ft_syntax)
 * 4th expansion of certain keywords with env-content
 * 5th a linked list for execution is created (ft_commands)
 * 
 * @param input the command line input from readline
 * @param big struct with all necessary information to run a command, 
 * the linked list of commands is saved here
 */
int	minishell_parsing(char *input, t_big *big)
{
	char	**input_arr;
	t_list	*lexx;

	lexx = NULL;
	input_arr = create_cleanarr(big, &input);
	free(input);
	input = NULL;
	if (!input_arr)
		return (0);
	lexx = ft_tokenizer(input_arr);
	ft_free(input_arr);
	input_arr = NULL;
	if (!lexx || ft_syntax(lexx))
	{
		big->exit_code = 2;
		ft_free_ll(&lexx);
		return (0);
	}
	ft_expa_precond(lexx, big);
	ft_commands(lexx, &big);
	ft_free_ll(&lexx);
	return (1);
}
