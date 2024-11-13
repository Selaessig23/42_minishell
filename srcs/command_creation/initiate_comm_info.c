#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the list of commands will be created as part of 
 * t_big big (cmdlist) which will be used in execution part later on
 */

void	ft_init_comminfo(t_lexer *node_content, t_data *comm_info, t_list *curr_lexx, t_big **p_big)
{
	// t_lexer	*node_content;

	// node_content = curr_lexx->content;
	if (node_content->token == 3 || node_content->token == 4)
		curr_lexx = ft_set_r_in(node_content, &comm_info, curr_lexx, p_big);
	else if (node_content->token == 5 || node_content->token == 6)
		curr_lexx = ft_set_r_out(node_content, &comm_info, curr_lexx, p_big);
	else
		if (*node_content->value)
			ft_add_arr_back(node_content->value, &comm_info);
	if (curr_lexx != NULL)
		curr_lexx = curr_lexx->next;
	if (curr_lexx != NULL)
		node_content = curr_lexx->content;
	// while (curr_lexx != NULL
	// 	&& (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
	// 	&& node_content->token != 1 && node_content->token != 2)
	// {
	// 	curr_lexx = curr_lexx->next;
	// 	if (curr_lexx != NULL)
	// 		node_content = curr_lexx->content;
	// }
}
