
#include "libft_bonus.h"

// a generic version of ft_lstadd_back
/*
void	ft_lstadd_back_gen(void **lst, void *new)
{
	void	*curr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}
*/