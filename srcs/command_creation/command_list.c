
#include "minishell.h"

/**
 * DESCRIPTION:
 * in this file the list of commands will be created as part of 
 * t_big big (cmdlist) which will be used in execution part later on
 */

/**
 * @brief this function counts 
 * 1) the total number of commands and writes it to t_big
 * 2) the position (number) of each command
 * 
 * big->exe variable is used for execution of parent type builtins
 * (exit, cd, unset,export). Full execution if `exe` is true, 
 * if `exe` is false - only checking for errors and assigns exit code.
 * 
 * @param comm the list where each node stands for a command 
 * that has to be counted
 * @param p_big a pointer to the big struct 
 * that holds all information to execute the 
 * commands, here the total amount of commands has to be written in
 */
static void	ft_count_commands(t_list *comm, t_big **p_big)
{
	t_list	*curr;
	t_big	*big;
	size_t	i;

	curr = comm;
	big = *p_big;
	i = 0;
	while (curr != NULL)
	{
		big->count_commds += 1;
		i += 1;
		((t_data *)curr->content)->commands_no = i;
		curr = curr->next;
	}
	if (big->count_commds == 1)
		big->exe = true;
	else
		big->exe = false;
}

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
	command_array_new = (char **)malloc(sizeof(char *) * (count + 2));
	if (!command_array_new)
		error_handling(2);
	if (count > 0)
		i += ft_arrcpy(&command_array_old, &command_array_new);
	command_array_new[i] = ft_strdup(token_value);
	if (!command_array_new[i])
		error_handling(2);
	i += 1;
	command_array_new[i] = NULL;
	comm_info->cmd = command_array_new;
	if ((command_array_old))
		ft_free(command_array_old);
}

/**
 * @brief function to set commands_no to
 * the current number and the rest of values 
 * of the command info struct to 0
 * 
 * @param p_comm_info pointer to the struct that 
 * should be set to zero
 * @param lexx to set a commands_no, by default it is
 * set to 1, if there is a pipe it previously increased
 * in function "ft_init_clist"
 */
static void	init_comm(t_data **p_comm_info, t_list *lexx)
{
	t_data	*comm_info;
	t_lexer	*lexx_deref;

	lexx_deref = lexx->content;
	comm_info = *p_comm_info;
	comm_info->cmd = ft_calloc(1, sizeof(char *));
	comm_info->commands_no = (size_t)lexx_deref->number_helper;
	comm_info->in_heredoc = false;
	comm_info->fd_infile = 0;
	comm_info->out_append = false;
	comm_info->fd_outfile = 1;
	comm_info->id = 0;
}

/**
 * @brief function increase a number of "number_helper"
 * it serves for creation of many heredocs files
 * 
 * @param curr_lexx is a linked list for "t_lexer" type of
 * struct. it containts "number_helper" integer that is used
 * for set a "commands_no" to t_data in each call of "ft_init_clist"
 * function
 * @param comm_info is a structure with a current number of
 * command. it is 1, if it was only 1 command before the fisrt
 * occurence of the pipe.
*/
static void set_number_helper(t_data *comm_info, t_list *curr_lexx)
{
	int	i;

	i = (int)comm_info->commands_no;
	i++;
	((t_lexer *)(curr_lexx->content))->number_helper = i;
}

/**
 * @brief this function initiate the linked list of commands by
 * checking the tokens of the command line input, opening all fds
 * and creating heredoc.
 * 
 * ft_set_r_in - for input redirection
 * ft_set_r_out - for out redirection
 * 
 * !would have been better to name the variable token in struct 
 * t_lexer tokentype instead of token!
 * variable "number_helper" helps to create many heredocs
 * 
 * @param lexx the expanded linked list with command line input 
 * @param comm linked list of commands which should be filled
 * with command information for each command (=node)
 * @param p_big pointer to the struct big to integrate the exit code in
 * case of an error when opening redirect out or in
 */
static void	ft_init_clist(t_list **lexx, t_list **comm, t_big **p_big)
{
	t_data	*comm_info;
	t_list	*curr_lexx;
	t_lexer	*token;

	comm_info = NULL;
	curr_lexx = *lexx;
	token = curr_lexx->content;
	comm_info = ft_calloc(1, sizeof(t_data));
	if (!comm_info)
		error_handling(2);
	init_comm(&comm_info, *lexx);
	while (curr_lexx != NULL && token->token != 1 && token->token != 2)
	{
		if (token->token == 3 || token->token == 4)
			curr_lexx = ft_set_r_in(token, &comm_info, curr_lexx, p_big);
		else if (token->token == 5 || token->token == 6)
			curr_lexx = ft_set_r_out(token, &comm_info, curr_lexx, p_big);
		else
			if (*token->value)
				ft_add_arr_back(token->value, &comm_info);
		if (curr_lexx != NULL)
			curr_lexx = curr_lexx->next;
		if (curr_lexx != NULL)
			token = curr_lexx->content;
		// ft_init_comminfo(token, comm_info, curr_lexx, big);
		while (curr_lexx != NULL
			&& (comm_info->fd_infile < 0 || comm_info->fd_outfile < 0)
			&& token->token != 1 && token->token != 2)
		{
			curr_lexx = curr_lexx->next;
			if (curr_lexx != NULL)
				token = curr_lexx->content;
		}
	}
	ft_lstadd_back(comm, ft_lstnew(comm_info));
	if (token->token == 1 || token->token == 2)
	{
		curr_lexx = curr_lexx->next;
		set_number_helper(comm_info, curr_lexx);
		ft_init_clist(&curr_lexx, comm, p_big);
	}
}

/**
 * @brief function to create a linked list of commands 
 * (for execution part)
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
	((t_lexer *)(lexx->content))->number_helper = 1;
	ft_init_clist(&lexx, &comm, p_big);
	ft_count_commands(comm, p_big);
	big->cmdlist = comm;
}
