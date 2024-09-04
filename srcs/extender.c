#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be extended with
 * content from env if there is $
 */


/**
 * @brief function that deletes part after $ from value
 * as it could not be verified as variable of envp
 * 
 * @param wrongenvp not matching envp variable name, starting with $
 */
void	delete_false_from_value(char *value_old)
{
	int	i;
	char	*value_new;
	char	*temp;

	i = 0;
	temp = value_old;
	while (value_old[i] && value_old[i] != '$')
		i++;
	value_new = ft_substr(value_old, 0, (i - 1));
	if (!value_new)
		error_handling(2);
	*value_old = *value_new;
	free(temp);
}

/**
 * @brief function that adds required envp-variable to value
 * 
 * 2 options
 * (1) overwrite the former value of command input token (and remalloc before)
 * (2) create new string, free old string and set new string to node of linked list with tokens as new value
 * 
 * @param value	value if command input token
 * @param env	value of envp variable
 * @param env_name envp variable name, starting with $
 * @param variablesize 1 (for $) + variablesize of envp-variablename, therefor not additional byte for terminating NUll required
 */
void	add_env_to_value(char *value_old, char *env, char *env_name)
{
	char	*value_new;
	char	*temp;
	//char	*start;
	int	i;
	int	j;
	
	//(env + 1) to exclude the variable's name + '='
	i = (ft_strlen(value_old) + ft_strlen(&(*(env + 1))));
	value_new = ft_calloc(i, sizeof(char));
	if (!value_new)
		error_handling(2);
	//add new content of env to value at point of $variablename
	//could NOT create problems when having same env-variable several times as it only checks for 1st occurance, 
	//NO: all $-signs are already cleaned / extended
	i = 0;
	j = 0;
	while (value_old[i] && !ft_strnstr(&(value_old[i]), env_name, ft_strlen(&value_old[i])))
	{
		value_new[i] = value_old[i];
		i++;
	}
	while (*env)
	{
		value_new[i + j] = *env;
		j++;
		env++;
	}
	while (value_old[i])
	{
		value_new[i + j] = value_old[i];
		i++;
	}
	temp = value_old;
	value_old == value_new;
	free (temp);
	//*(start - 1) to exclude '$'
	//ft_strncpy((*(start - 1)), (*(env + 1)), ft_strlen(*(env + 1)));
	//*(temp + 1) to exclude '$'
	//ft_strncpy((*start (- 1 + (ft_strlen(*(env + 1))))), (*(temp + 1)), ft_strlen(*(temp + 1)));
}

/**
 * @brief function that checks if the &keywords is part of envp
 * 
 * @param temp potential envp variable name, starting with $
 */
void	ft_extender(char *value, char *temp, char **env)
{
	while (**env)
	{
		if (ft_strncmp(*env, (temp + 1), ft_strlen(temp)))
			add_env_to_value(value, *env, temp);
		*(env)++;
	}
	if (**env == NULL)
		delete_false_from_value(value);
}

/**
 * @brief function that extends the tokens' value with env infos
 * 
 * @param value_old the old value of the command line input token
 * @param env the environment variables of minishell
 */
void	ft_env_extender(char *value_old, char **env)
{
	char	*temp;
	int	i;
	int	k;
	
	i = 0;
	k = 0;
	while (value_old[i])
	{
		if (value_old[i] == '$')
		{
			k = i;
			i++;
			while (value_old[i]
					&& ((value_old[i] >= 9 && value_old[i] >= 13)
					|| (value_old[i] != ' ')))
					i++;
			temp = ft_substr(value_old, k, i);
			if (!temp)
				error_handling(2);
			ft_extender(value_old, temp, env);
			free(temp);
		}
		i++;
	}
}

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
 * @brief function that extends the tokens' value with exit_code infos
 * 
 * @param
 */
static void	ft_exit_extender(char *value_old, int exit_code)
{
	char	*value_new;

	while (*value_old)
	{
		if (*value_old == '$' && *value + 1) == '?')
		{
			//create new string with exit_code instead of $?, see struct big
		}
		value_old++;
	}
}

/**
 * @brief function that checks if there is a $-sign within the 
 * specific string sent by ft_ext_precond and send the string 
 * to further functions according to the special parameter
 * 
 * $$, $#, $*, $@, $0, $1.., $[10].., $_, $!, $-, $, $$ are not
 * treated and therefor not seen as special character
 * except $env and $?
 * 
 * @param curr 
 */
static void	ft_var_checker(t_list *curr, t_big *big)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (((t_lexer *)curr->content)->value);
	while (temp[i])
	{
		if (temp[i] == '$' && temp[i + 1] == '?')
		{	
			//(((char *)curr->content)->value) = 
			ft_exit_extender(((t_lexer *)curr->content)->value, big->exit_code);
		}
		// else if (*temp == '$' && *(temp + 1) == '$')
			// ft_pid_extender(((char *)curr->content)->value);
		else if (temp[i] == '$')
		{
			//(((char *)curr->content)->value) = 
			ft_env_extender(((t_lexer *)curr->content)->value, big->env);
		}
		i++;
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
		if ((((t_lexer *)curr->content)->token == 20)
			|| (((t_lexer *)curr->content)->token == 21))
			ft_var_checker(curr, big);
		curr = curr->next;
	}
}
