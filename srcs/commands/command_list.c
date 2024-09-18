
#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the list of commands will be created as part of 
 * t_big big (cmdlist) which will be used in execution part later on
 */

/**
 * @brief function to create an array of commands (**cmd) which 
 * will serve as argv in execution part
 * 
 * @param token_value the value of the specific token (node) of the 
 * command line input that has to be added to **cmd
 * @param p_comm_info pointer to the struct of command information
 */
void	ft_add_arr_back(char *token_value, t_data **p_comm_info)
{
	t_data	*comm_info;
	char	**command_array_old;
	char	**command_array_new;
	size_t	count;
	size_t	i;

	i = 0;
	comm_info = *p_comm_info;
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
	comm_info->cmd = command_array_new;
	// printf("what the hack B: %s\n", *p_command_array[0]);;
	// printf("what the hack B: %s\n", comm_info->cmd[0]);;
	if ((command_array_old))
		ft_free(command_array_old);
}

/**
 * @brief function to set all values 
 * of the command info struct to 0
 * 
 * @param p_comm_info pointer to the struct that 
 * should be set to zero
 */
void	init_comm_zero(t_data **p_comm_info)
{
	t_data	*comm_info;

	comm_info = *p_comm_info;
	comm_info->cmd = ft_calloc(1, sizeof(char *));
	comm_info->commands_no = 1;
	comm_info->in_heredoc = false;
	comm_info->infile = NULL;
	comm_info->out_append = false;
	comm_info->outfile = NULL;
}

/**
 * @brief this function initiate the linked list of commands by
 * checking the tokens of the command line input
 * 
 * !would have been better to name the variable token in struct 
 * t_lexer tokentype instead of token!
 * 
 * @param lexx the expanded linked list with command line input 
 * @param comm linked list of commands which should be filled
 * with command information for each command (=node)
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
 * which should be part of the struct big (cmdlist)
 * 
 * @param lexx the expanded linked list with command line input
 * @param p_big pointer to the struct big to integrate a linked list of
 * commands to (cmdlist)
 */
void	ft_commands(t_list *lexx, t_big **p_big)
{
	t_list	*comm;
	t_big	*big;

	big = *p_big;
	comm = NULL;
	// printf("what the hack I\n");
	ft_init_clist(&lexx, &comm);
	big->cmdlist = comm;
}
