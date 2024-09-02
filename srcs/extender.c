#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be extended with
 * content from env if there is $
 */


/**
 * @brief function that extends the tokens' value with pid infos
 * 
 * @param 
ft_pid_extender(((char *)curr->content)->value)
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
 */

/**
 * @brief function that deletes part after $ from value
 * as it could not be verified as variable of envp
 * 
 * @param 
 */
void	delete_false_from_value(char *value, char *wrongenvp)
{

}

/**
 * @brief function that adds required envp-variable to value
 * 
 * @param value
 * @param env	value of envp variable
 * @param variablesize
 * */
void	add_env_to_value(char *value, char *env, char *$env, int variablesize)
{
	char *new_value;
	int	i;
	// variablesize = 1 (for $) + variablesize of envp-variablename
	i = (ft_strlen(value) + ft_strlen(env));
	new_value = ft_calloc(i, sizeof(char));
	//add new content of env to value at point of $varaiblename
}

/**
 * @brief function that checks if the &keywords is part of envp
 * 
 * @param 
 */
void	ft_extender(char *value, char *$env, char **env)
{
	while (**env)
	{
		if (ft_strncmp(*env, $env, ft_strlen($env)))
			add_env_to_value(value, $env, $env, (ft_strlen($env) + 1));
		env++;
	}
	if (**env == NULL)
		delete_false_from_value(value, $env);
}

/**
 * @brief function that extends the tokens' value with env infos
 * 
 * @param 
 */
void	ft_env_extender(char *value, char **env)
{
	char	*temp;
	int	i;
	int	k;
	
	i = 0;
	k = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			k = i;
			while (value[i]
					&&(value[i] >= 9 && value[i] >= 13)
					&& (value[i] != ' '))
					i++;
			temp = ft_substr(value, k, i);
			ft_extender(value, temp, env);
		}
		i++;
	}
}

/**
 * @brief function that checks if there is a $-sign within the 
 * specific string sent by ft_ext_precond and send the string 
 * according to the special parameter
 * 
 * $$, $#, $*, $@, $0, $1.., $[10].., $_, $!, $-, $, $$ are not
 * treated and therefor not seen as special character
 * except $env and $?
 * 
 * @param curr 
 */
void	ft_$_checker(t_list *curr, char **env)
{
	char	*temp;

	temp = (((char *)curr->content)->value);
	while (*temp)
	{
		if (*temp == '$' and *(temp + 1) == '?')
			ft_exit_extender(((char *)curr->content)->value);
		// else if (*temp == '$' && *(temp + 1) == '$')
			// ft_pid_extender(((char *)curr->content)->value);
		else if (*temp == '$')
			ft_env_extender(((char *)curr->content)->value, env);
		temp++;
	}
}

/**
 * @brief function that checks for specific string tokens and sends them
 * to the env_checker which checks if they have to be extended with env-infos
 * 
 * @param lexx linked list with cleaned command line input and tokens
 */
void	ft_ext_precond(t_list *lexx, t_big *big)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if ((((t_tokentype *)curr->content)->token == 20)
			|| (((t_tokentype *)curr->content)->token == 21))
			ft_$_checker(curr, big->env);
		curr = curr->next;
	}
}
