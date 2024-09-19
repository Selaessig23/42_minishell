
#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the list of commands will be created as part of 
 * t_big big (cmdlist) which will be used in execution part later on
 */

/**
 * @brief (helper) function (for to ft_add_arr_back) to add existing 
 * strings from command_array_old to command_array_new
 * 
 * @param p_old pointer to the old command array (to copy from)
 * @param p_new pointer to the new command array (to copy to)
 */
static int	ft_arrcpy(char ***p_old, char ***p_new)
{
	int		i;
	char	**old;
	char	**new;

	i = 0;
	if (*p_old == NULL)
		return (0);
	old = *p_old;
	new = *p_new;
	while (old[i] != NULL)
	{
		// printf("what the hack A-b, count\n");
		new[i] = ft_strdup(old[i]);
		i++;
	}
	return (i);
}

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
		i += ft_arrcpy(&command_array_old, &command_array_new);
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
 * @brief function to set values of command struct in case of
 * redirection out (> or >>)
 * 
 * @param token the specific token (node) of the command line input
 * which stands for the redirection symbol
 * @param comminfo pointer to the struct that holds the command infos
 * @param lexx the expanded linked list with command line input 
 */
static t_list	*ft_set_r_out(t_lexer *token, t_data **cominfo, t_list *lexx)
{
	t_data	*comm_info;

	comm_info = *cominfo;
	if (token->token == 6)
		comm_info->out_append = true;
	lexx = lexx->next;
	token = lexx->content;
	comm_info->outfile = ft_strdup(token->value);
	return (lexx);
}

/**
 * @brief function to set values of command struct in case of
 * redirection in (<) or heredoc-signal (<<)
 * 
 * @param token the specific token (node) of the command line input
 * which stands for the redirection symbol
 * @param comminfo pointer to the struct that holds the command infos
 * @param lexx the expanded linked list with command line input 
 */
static t_list	*ft_set_r_in(t_lexer *token, t_data **cominfo, t_list *lexx)
{
	t_data	*comm_info;

	comm_info = *cominfo;
	if (token->token == 3)
		comm_info->in_heredoc = true;
	lexx = lexx->next;
	token = lexx->content;
	comm_info->infile = ft_strdup(token->value);

	return (lexx);
}

/**
 * @brief function to set all values 
 * of the command info struct to 0
 * 
 * @param p_comm_info pointer to the struct that 
 * should be set to zero
 */
static void	init_comm_zero(t_data **p_comm_info)
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
	// char	**test_arr;

	// comm_info = NULL;
	// test_arr = NULL;
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
		if (token->token == 3 || token->token == 4) //heredoc or redirect in
			curr_lexx = ft_set_r_in(token, &comm_info, curr_lexx);
		else if (token->token == 5 || token->token == 6) //redirect out or redirect out append
			curr_lexx = ft_set_r_out(token, &comm_info, curr_lexx);
		else //strings become part of command_array
		{
			ft_add_arr_back(token->value, &comm_info);
			// test_arr = comm_info->cmd;
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

	if (!lexx)
		error_handling(0);
	big = *p_big;
	comm = NULL;
	// printf("what the hack I\n");
	ft_init_clist(&lexx, &comm);
	big->cmdlist = comm;
}
