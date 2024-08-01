/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:54:51 by mpeshko           #+#    #+#             */
/*   Updated: 2024/06/07 20:07:23 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Iterates through a linked list ‘lst’ and applies the function ‘f’ to each
node’s content. If ‘lst’ or ‘f’ is NULL, the function returns. The loop runs
while there are still nodes in the list. Within each iteration, the ‘f’ function
is called with the content of the current node, and the ‘lst’ pointer is moved
to the next node in the list.*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
