/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:21:59 by mstracke          #+#    #+#             */
/*   Updated: 2025/01/29 15:25:47 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief function that organises the splitting of
 * command line input (=string) to an array of strings,
 * separators are tabs, spaces
 * 
 * @param readline_input the genuine command line input string* 
 * @param clean_input the cleaned (prepared) command line input string
 */
char	**ft_split_rlinput(char **readline_input, char *clean_input)
{
	char	**input_arr;

	input_arr = ft_split_quotes(clean_input, ' ');
	if (!input_arr)
	{
		free(clean_input);
		clean_input = NULL;
		ft_free(readline_input);
		readline_input = NULL;
		error_and_exit(2);
	}
	return (input_arr);
}
