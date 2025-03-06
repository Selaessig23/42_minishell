/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_specials.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:53:34 by mstracke          #+#    #+#             */
/*   Updated: 2025/03/06 10:16:05 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESCRIPTION: 
 * in this file two special fuctions are listed, that 
 * enlarge functionality of genuine ft_split-function
 * of libft, modified for minishell-purposes
 */

/**
 * @brief function that checks the precense of tabs and spaces
 * 
 * @param c char to check for tabs
 */
int	is_tab(char c)
{
	if ((c >= 9 && c <= 13)
		|| c == ' ')
		return (1);
	else
		return (0);
}

/**
 * @brief function that iterates s if c | spaces || tabs
 * by doing so, it considers more than one separator 
 * (not only c, but also spaces and tabs)
 * 
 * @param s string to search in
 * @param c char to search for (beside tabs)
 * @param i the index to start iterating from
 */
int	ft_space_tab_jump(const char *s, char c, int i)
{
	while (s[i] && (s[i] == c 
			|| is_tab(s[i]) || s[i] == ' '))
		i++;
	return (i);
}

/**
 * @brief function to exclude content within quotation marks from splitting
 * 
 * @param s string to search in for quotation marks
 * @param i the index to start searching
 */
int	ft_quo_handling(const char *s, int i)
{
	if (s[i] == '\'')
	{
		if (s[i + 1] != '\0')
			i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	else if (s[i] == '\"')
	{
		if (s[i + 1] != '\0')
			i++;
		while (s[i] && s[i] != '\"')
			i++;
	}
	if (s[i] == '\0')
		i--;
	return (i);
}
