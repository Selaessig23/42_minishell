
#include "minishell.h"

/**
 * DESCRIPTION
 * 
 */

/**
 * @brief function to check for built-in-commands
 */
int	ft_builtin_checker(t_data *comm_info, t_big *big, char *prompt)
{
	char	**cmds;

	cmds = comm_info->cmd;
	if (cmds[0] && !ft_strncmp(cmds[0], "echo", ft_strlen(cmds[0])))
	{
		//integrate link to echo-function here
		return (1);
	}
	else if (cmds[0] && !ft_strncmp(cmds[0], "cd", ft_strlen(cmds[0])))
	{
		//integrate link to cd-function here
		return (1);
	}
	else if (cmds[0] && !ft_strncmp(cmds[0], "pwd", ft_strlen(cmds[0])))
	{
		//integrate link to pwd-function here
		return (1);
	}
	else if (cmds[0] && !ft_strncmp(cmds[0], "export", ft_strlen(cmds[0])))
	{
		//integrate link to export-function here
		return (1);
	}
	else if (cmds[0] && !ft_strncmp(cmds[0], "unset", ft_strlen(cmds[0])))
	{
		//integrate link to unset-function here
		return (1);
	}
	else if (cmds[0] && !ft_strncmp(cmds[0], "env", ft_strlen(cmds[0])))
	{
		ft_print_env(big);
		return (1);
	}
	else if (cmds[0] && !ft_strncmp(cmds[0], "exit", ft_strlen(cmds[0])))
	{
		ft_exit_minishell(big, prompt);
		return (2);
	}
	else
		return (0);
}


/**
 * @brief function to organises the execution part
 */
int    ft_executer(t_big *big, char *prompt)
{
	t_list  *curr;
	t_data  *comm_info;

	curr = big->cmdlist;
	comm_info = curr->content;
	while (curr != NULL)
	{
		comm_info = curr->content;
		if (ft_builtin_checker(comm_info, big, prompt))
			printf("---------------------------------------------\n");
			// return (1);
		else
			ft_test_command_print(prompt, comm_info);
		curr = curr->next;
	}
	ft_free_cl(&(big->cmdlist));
	return (0);
}
