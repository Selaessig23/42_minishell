
#include "minishell.h"

/**
 * @brief function to free the linked list
 * 
 * @param ll the linked list to free
 */
void	ft_free_cl(t_list **ll)
{
	t_list	*temp;
	t_list	*curr;

	curr = *ll;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(((t_data *)temp->content)->infile);
        free(((t_data *)temp->content)->outfile);
        ft_free(((t_data *)temp->content)->cmd);
		free(temp->content);
		free(temp);
	}
	curr = NULL;
}