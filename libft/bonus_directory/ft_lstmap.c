/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:55:25 by mpeshko           #+#    #+#             */
/*   Updated: 2024/06/07 20:06:21 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Creates a new linked list by applying the function ‘f’ to the content of
each node in the input list ‘lst’. If ‘lst’, ‘f’, or ‘del’ is NULL or if memory
allocation fails, it returns NULL. It uses ‘lst_new’ to create new nodes and
links them together to form the resulting list. If any memory allocation fails
during the process, it clears the already created nodes and returns NULL.
The ‘del’ function is used to free the memory allocated for each node’s
content if needed. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*elem;

	new_lst = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		elem = ft_lstnew((*f)(lst->content));
		if (!elem)
		{
			ft_lstclear(&new_lst, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new_lst, elem);
		lst = lst->next;
	}
	return (new_lst);
}
