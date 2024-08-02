/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:54:35 by mpeshko           #+#    #+#             */
/*   Updated: 2024/06/07 20:08:38 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

/* Clears the entire linked list pointed to by ‘lst’ and deallocates memory
for each node. The ‘del’ function is used to free the memory associated with
the content of each node. If ‘lst’ is NULL, ‘del’ is NULL, or the list is
already empty, the function returns. The function recursively calls itself with
the next node until the end of the list is reached. Then, it frees the content
of the current node, deallocates the node itself, and sets ‘lst’ to NULL.*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !del || !(*lst))
		return ;
	ft_lstclear(&(*lst)->next, del);
	del((*lst)->content);
	free(*lst);
	*lst = NULL;
}
