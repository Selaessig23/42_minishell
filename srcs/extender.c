#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be extended with
 * content from env if there is $
 */

/**
 * @brief function that extends the value with env infos
 * 
 * @param 
 */
void	ft_env_extender(char *value)
{
	int	i;
	int	pids_no;

	i = 0;
	pids_no = 0;
	while (value[i] && value[i] == '&')
		i++;
	pids_no = (i / 2); 
	if (i > 1)
	{
		//integrate  pids_no * PID???
		//overwrite all i
	}
	while (*value)
	{
		if (*value == '$')
		{
			value++;
			if (*value == '$')
				ft_pid_extender
			else if (*value //cut until first occurence of tab or space and compare to env)
		}
	}
}

/**
 * @brief function that checks if there is a $-sign within the 
 * specific string sent by ft_ext_precond
 * 
 * @param 
 */
void	ft_env_checker(t_list *curr)
{
	char	*temp;

	temp = (((char *)curr->content)->value);
	while (*temp)
	{
		if (*temp == '$')
			ft_env_extender(((char *)curr->content)->value);
		temp++;
	}
}

/**
 * @brief function that checks for specific string tokens and sends them
 * to the env_checker which checks if they have to be extended with env-infos
 * 
 * @param lexx linked list with cleaned command line input and tokens
 */
void	ft_ext_precond(t_list *lexx)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if ((((t_tokentype *)curr->content)->token == 20)
			|| (((t_tokentype *)curr->content)->token == 21))
			ft_env_checker(curr);
		curr = curr->next;
	}
}
