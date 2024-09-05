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
char	*delete_false_from_value(char *value_old, char *wrongenvp)
{
	int		i;
	char	*value_new;
	char	*temp;

	i = 0;
	temp = value_old;
	printf("test 3A: value_old: %s\nwrongenvp: %s\n", value_old, wrongenvp);
	i = (ft_strlen(value_old) - ft_strlen(wrongenvp));
	value_new = ft_calloc((i + 1), sizeof(char));
	if (!value_new)
		error_handling(2);
	i = 0;
	while (value_old[i] && (!ft_strnstr(&(value_old[i]), wrongenvp, ft_strlen(wrongenvp))))
	{
		value_new[i] = value_old[i];
		i++;
	}
	while (value_old[i + ft_strlen(wrongenvp)])
	{
		value_new[i] = value_old[i + ft_strlen(wrongenvp)];
		i++;
	}
	value_new[i] = '\0';
	printf("test 4B value_new: %s\n", value_new);
	return (value_new);
	// value_old = value_new;
	// free(temp);
}

/**
 * @brief function that adds required envp-variable to value
 * 
 * 2 options
 * (1) overwrite the former value of command input token (and remalloc before)
 * (2) create new string, free old string and set new string to node of linked list with tokens as new value
 * 
 * @param value	value of command input token
 * @param env	value of env variable
 * @param env_name envp variable name, starting with $
 * @param variablesize 1 (for $) + variablesize of envp-variablename, therefor not additional byte for terminating NUll required
 */
char	*add_env_to_value(char *value_old, char *env, char *env_name)
{
	char	*value_new;
	// char	*temp;
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
	printf("test 3A: %s\nvalue_old: %s\n", (env), value_old);
	while (value_old[i] && (!ft_strnstr(&(value_old[i]), env_name, ft_strlen(env_name))))
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
	while (value_old[i + ft_strlen(env_name)])
	{
		value_new[i + j] = value_old[i + ft_strlen(env_name)];
		i++;
	}
	value_new[i + j] = '\0';
	// temp = value_old;
	// value_old = value_new;
	printf("test 4A\n");
	return (value_new);
	// free (temp);
	//*(start - 1) to exclude '$'
	//ft_strncpy((*(start - 1)), (*(env + 1)), ft_strlen(*(env + 1)));
	//*(temp + 1) to exclude '$'
	//ft_strncpy((*start (- 1 + (ft_strlen(*(env + 1))))), (*(temp + 1)), ft_strlen(*(temp + 1)));
}

/**
 * @brief function that checks if the &keywords is part of envp
 * 
 * @param temp potential env variable name, starting with $
 */
char	*ft_extender(char *value, char *temp, char **env)
{
	printf("env variable name: %s\nlength: %zu\n", (temp + 1), ft_strlen(temp + 1));
	while (env && *env)
	{
		printf("test 2A: %s\n", *env);
		if (!ft_strncmp(*env, (temp + 1), ft_strlen(temp + 1)))
		{
			return (add_env_to_value(value, (*env + (ft_strlen(temp + 1) + 1)), temp));
		}
		env++;
	}
	printf("test2B\n");
	return (delete_false_from_value(value, temp));
	
}

/**
 * @brief function that extends the tokens' value with env infos
 * by searching for 1st occurance of $ and the following variable name,
 * than sending this to ft_extender
 * 
 * @param value_old the old value of the command line input token
 * @param env the environment variables of minishell
 */
char	*ft_env_extender(char *value_old, char **env)
{
	char	*temp;
	char	*value_new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	value_new = NULL;
	while (value_old[i])
	{
		if (value_old[i] == '$')
		{
			k = i;
			i++;
			while (value_old[i]
					&& ((value_old[i] < 9 || value_old[i] > 13)
					&& (value_old[i] != ' ')))
					i++;
			temp = ft_substr(value_old, k, (i - k));
			printf("Variable name to search for: %s\n", temp);
			if (!temp)
				error_handling(2);
			value_new = ft_extender(value_old, temp, env);
			free(temp);
			printf("test 5\n");
			return (value_new);
		}
		i++;
	}
	return (value_old);
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

	(void) value_new;
	(void) exit_code;
	while (*value_old)
	{
		if (*value_old == '$' && *(value_old + 1) == '?')
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
static void	ft_var_checker(void	**token, t_big *big)
{
	t_lexer	*temp;
	char	*temp2;
	int		i;

	i = 0;
	// temp2 = *curr;
	// temp = (((t_lexer *)temp2->content)->value);
	temp = *token;
	temp2 = temp->value;
	while (temp2[i])
	{
		if (temp2[i] == '$' && temp2[i + 1] == '?')
		{
			//(((char *)curr->content)->value) = 
			// ft_exit_extender(((t_lexer *)temp->content)->value, big->exit_code);
			ft_exit_extender(temp2, big->exit_code);
		}
		// else if (*temp == '$' && *(temp + 1) == '$')
			// ft_pid_extender(((char *)curr->content)->value);
		else if (temp2[i] == '$')
		{
			// temp2 = *((t_lexer *)curr->content)->value;
			// (((t_lexer *)curr->content)->value) = &(ft_env_extender(((t_lexer *)curr->content)->value, big->env));
			((t_lexer *)token)->value = ft_env_extender(temp2, big->env);
			printf("test 6: %s\n", ((t_lexer *)token)->value);
			free (temp);
		}
		i++;
	}
}

/**
 * @brief this functions deletes quotation marks at the beginning and end of
 * the value of token single_quoted / double_quoted
 * 
 * DO I HAVE TO ENSURE THAT value_old has enough characters to remove quotes?
 * 
 * @param 
 */
void	ft_quote_remover(void **token)
{
	char	*value_new;
	t_lexer	*temp;
	char	*value_old;
	int		i;

	i = 0;
	temp = *token;
	value_old = temp->value;
	value_new = ft_calloc(((ft_strlen(value_old) - 2) + 1), 
			sizeof(char));
	while (value_old[i + 1] && value_old[i + 1] != '\"') 
	{
		value_new[i] = value_old[i + 1];
		i += 1;
	}
	value_new[i] = '\0';
	temp->value = value_new;
	printf ("Calloc: %lu, real: %zu\n",((ft_strlen(value_old) - 2)), ft_strlen(value_new));
	free(value_old);
}

/**
 * @brief function that organises the expansion and reduction
 * of command line input by checking for specific string tokens
 * 
 * MISSING, if we want to handle UNCLOSED QUOTES: delete them
 * 
 * @param lexx linked list with cleaned command line input and tokens
 */
void	ft_ext_precond(t_list *lexx, t_big *big)
{
	t_list	*curr;

	curr = lexx;
	while (curr != NULL)
	{
		if ((((t_lexer *)curr->content)->token == 21)
			|| (((t_lexer *)curr->content)->token == 22))
			ft_quote_remover(&curr->content);
		if ((((t_lexer *)curr->content)->token == 20)
			|| (((t_lexer *)curr->content)->token == 21))
		{
			ft_var_checker(&curr->content, big);
			printf("test 7: %s\n", (((t_lexer *)curr->content)->value));
		}
		curr = curr->next;
	}
}
