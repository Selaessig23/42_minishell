/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_to_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:56:50 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/13 13:58:29 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * this file serves to organise the transformation from a
 * linked list to a string
 */

/**
 * @brief function to copy from src to dest
 * 
 * @param dest the string to copy in
 * @param src the string to copy from
 */
static char	*ft_strcpy(char *dest, const char *src)
{
	if (!src)
		return (NULL);
	while (*src)
	{
		*dest = *src;
		dest += 1;
		src += 1;
	}
	return (dest);
}

/**
 * @brief helper function for ft_listtostr to count the
 * size of each string of the linked list
 * 
 * @param q_word_list the linked list in wich the strings of 
 * (void) content have to be counted
 */
static size_t	ft_count_str_in_ll(t_list *q_word_list)
{
	t_list	*curr;
	char	*str_to_count;
	size_t	count_str;

	curr = q_word_list;
	count_str = 0;
	while (curr != NULL)
	{
		str_to_count = ((t_lexer *)curr->content)->value;
		count_str += ft_strlen(str_to_count);
		curr = curr->next;
	}
	return (count_str);
}

/**
 * @brief function that transforms a linked list to a 
 * single string
 *  
 * @param arr the array of strings to read from
 */
char	*ft_listtostr(t_list *q_word_list)
{
	t_list	*curr;
	char	*str;
	int		count_str;
	int		j;

	curr = q_word_list;
	count_str = ft_count_str_in_ll(q_word_list);
	j = 0;
	str = ft_calloc(((count_str) + 1), sizeof(char));
	curr = q_word_list;
	while (curr != NULL)
	{
		j = ft_strlen(str);
		ft_strcpy(&str[j], ((t_lexer *)curr->content)->value);
		curr = curr->next;
	}
	str[count_str] = '\0';
	return (str);
}
