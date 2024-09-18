
#include "minishell.h"

/**
 * DESCRIPTION:
 * file which holds all functions of feat command
 * that are required by more than one function
 */

/**
 * @brief function to free the linked list of commands
 * 
 * @param ll the linked list to free
 */
void	ft_free_cl(t_list **ll)
{
	t_list	*temp;
	t_list	*curr;
	t_data	*comm_info;

	curr = *ll;
	while (curr != NULL)
	{
		temp = curr;
		comm_info = temp->content;
		curr = curr->next;
		free(comm_info->infile);
		free(comm_info->outfile);
		ft_free(comm_info->cmd);
		free(comm_info);
		free(temp);
	}
	curr = NULL;
}
