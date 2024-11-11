
#include "minishell.h"

void	exe_fd_error(t_big *big, t_data *comm_info_next)
{
	big->exit_code = 1;
	if (comm_info_next && comm_info_next->fd_infile == 0)
		comm_info_next->fd_infile = open("/dev/null", O_RDONLY);
}

t_data	*ft_pointer_next_command(t_list	*curr)
{
	if (curr->next != NULL)
		return (curr->next->content);
	else
		return (NULL);
}

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
		// free(comm_info->infile);
		// free(comm_info->outfile);
		ft_free(comm_info->cmd);
		free(comm_info);
		free(temp);
	}
	curr = NULL;
}
