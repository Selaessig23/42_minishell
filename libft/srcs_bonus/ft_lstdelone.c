/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 00:54:43 by mpeshko           #+#    #+#             */
/*   Updated: 2024/06/07 20:07:57 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

/*Deletes a single node ‘lst’ from the linked list and frees its content using
the ‘del’ function, then deallocates the memory for the node. However, it fails
to remove ‘lst’ from the list fully, as it only sets the local ‘lst’ pointer
to NULL. The list re-linking must be done externally.*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
