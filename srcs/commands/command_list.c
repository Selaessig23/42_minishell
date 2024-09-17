
#include "minishell.h"

/**
 * DESCRIPTION
 * 
 */

/**
 * @brief function to define infile and in_heredoc
 */



/**
 * @brief function to create array of commands
 */
// void	ft_add_arr_back(char *token_value, char ***p_command_array)
void	ft_add_arr_back(char *token_value, t_data **p_comm_info)
{
	t_data	*comm_info;
	char	**command_array_old;
	char	**command_array_new;
	size_t	count;
	size_t	i;

	i = 0;
	comm_info = *p_comm_info;
	// command_array_old = *p_command_array;
	command_array_old = comm_info->cmd;
	count = ft_arrlen(command_array_old);
	// printf("what the hack A, count:: %zu\n", count);
	command_array_new = (char **)malloc(sizeof(char *) * (count + 2));
	if (!command_array_new)
		error_handling(2);
	if (count > 0)
	{
		// printf("what the hack A-a, count\n");
		while (command_array_old[i] != NULL)
		{
			// printf("what the hack A-b, count\n");
			command_array_new[i] = ft_strdup(command_array_old[i]);
			i++;
		}
	}
	// printf("what the hack A-c, count\n");
	command_array_new[i] = ft_strdup(token_value);
	// printf("what the hack A-d, count\n");
	if (!command_array_new[i])
		error_handling(2);
	i += 1;
	command_array_new[i] = NULL;
	// p_command_array = &command_array_new;
	comm_info->cmd = command_array_new;
	// printf("what the hack B: %s\n", *p_command_array[0]);;
	// printf("what the hack B: %s\n", comm_info->cmd[0]);;
	if ((command_array_old))
		ft_free(command_array_old);
}

/**
 * @brief function to set all values to 0
 * 
 * @param pointer_comm_info pointer to the struct the should be set to zero
 */
void	init_comm_zero(t_data **pointer_comm_info)
{
	t_data	*comm_info;

	comm_info = *pointer_comm_info;
	comm_info->cmd = ft_calloc(1, sizeof(char *));
	comm_info->commands_no = 1;
	comm_info->in_heredoc = false;
	comm_info->infile = NULL;
	comm_info->out_append = false;
	comm_info->outfile = NULL;
}

/**
 * @brief this function initiate the linked list of commands
 * 
 * would have been better to name the variable token in struct 
 * t_lexer tokentype instead of token
 * 
 * @param input_arr the cleaned array of strings created out of the 
 * command line input
 * @param lexx linked list to prepare all important variables for
 * syntax analysis
 */
static void	ft_init_clist(t_list **lexx, t_list **comm)
{
	t_data	*comm_info;
	t_list	*curr_lexx;
	t_lexer	*token;
	char	**test_arr;

	comm_info = NULL;
	test_arr = NULL;
	curr_lexx = *lexx;
	token = curr_lexx->content;
	comm_info = ft_calloc(1, sizeof(t_data));
	if (!comm_info)
		error_handling(2);
	// printf("what the hack II\n");
	init_comm_zero(&comm_info); //set all values to zero
	while (curr_lexx != NULL && token->token != 1 && token->token != 2)
	{
		// token = curr_lexx->content;
		// printf("what the hack III\n");
		if (token->token == 3) //heredoc
		{
			comm_info->in_heredoc = true;
			curr_lexx = curr_lexx->next;
			token = curr_lexx->content;
			comm_info->infile = ft_strdup(token->value);
		}
		else if (token->token == 4) //redirect in
		{
			// printf("test1\n");
			curr_lexx = curr_lexx->next;
			// printf("test2\n");
			token = curr_lexx->content;
			// printf("test3\n");
			comm_info->infile = ft_strdup(token->value);
			// printf("test4\n");
		}
		else if (token->token == 5) //redirect out
		{
			curr_lexx = curr_lexx->next;
			token = curr_lexx->content;
			comm_info->outfile = ft_strdup(token->value);
		}
		else if (token->token == 6) //redirect out append
		{
			comm_info->out_append = true;
			curr_lexx = curr_lexx->next;
			token = curr_lexx->content;
			comm_info->outfile = ft_strdup(token->value);
		}
		else //strings become part of command_array
		{
			ft_add_arr_back(token->value, &comm_info);
			test_arr = comm_info->cmd;
			// printf("what the hack IV: %s\n", test_arr[0]);
		}
		// printf("test5\n");
		curr_lexx = curr_lexx->next;
		if (curr_lexx != NULL)
			token = curr_lexx->content;
	}
	// printf("test6\n");
	ft_lstadd_back(comm, ft_lstnew(comm_info));
	// printf("what the hack V\n");
	if (token->token == 1 || token->token == 2)
	{
		// printf("recursive\n");
		ft_init_clist(&curr_lexx->next, comm);
	}
	// printf("what the hack VI\n");
}

/**
 * @brief function to create a linked list of commands
 */
void	ft_commands(t_list *lexx, t_big **p_big)
{
	t_list	*lexx_curr;
	t_list	*comm;
	t_list	*comm_curr;
	t_lexer	*token;
	t_big	*big;
	// t_data	*testprint;

	lexx_curr = lexx;
	token = lexx_curr->content;
	big = *p_big;
	comm = NULL;
	comm_curr = comm;
	// printf("what the hack I\n");
	ft_init_clist(&lexx, &comm);
	big->cmdlist = comm;
	// printf("test7\n");
	// while (curr != NULL)
	// {

	// 	if (token == 1 || token == 2)

	// 	curr = curr->next;
	// 	token == ((t_lexer)->content)->token;
	// }
	// printf("what the hack VII\n");
	// testprint = comm->next->content;
	// printf("arrayprint: %s\n", testprint->cmd[0]);
	// return (comm);
}
