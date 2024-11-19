/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:23:04 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 12:23:18 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief function to free the linked list
 * 
 * @param ll the linked list to free
 */
void	ft_free_ll(t_list **ll)
{
	t_list	*temp;
	t_list	*curr;

	curr = *ll;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(((t_lexer *)temp->content)->value);
		free(temp->content);
		free(temp);
	}
	curr = NULL;
}

/**
 * @brief function to check which kind of quote comes first
 * function serves to avoid that quotations (e. g. ') 
 * within main quotations (e . g. "), are taken into account
 * 
 * @param content the string to search in
 * @param checker the char to search for
 * 
 * @return returns 0 if checker char is not 1st quotation found
 */
int	ft_check_fstquote(char *content, char checker)
{
	char	counterpart;
	int		count_counter;
	int		count_checker;

	count_counter = 0;
	count_checker = 0;
	if (checker == '\'')
		counterpart = '\"';
	else if (checker == '\"')
		counterpart = '\'';
	else
		counterpart = '\0';
	while (content[count_counter] && content[count_counter] != counterpart)
		count_counter += 1;
	while (content[count_checker] && content[count_checker] != checker)
		count_checker += 1;
	if ((count_counter + count_checker) == 0 
		|| (count_counter - count_checker) == 0 
		|| count_counter < count_checker)
		return (1);
	else
		return (0);
}
