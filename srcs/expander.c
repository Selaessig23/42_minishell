#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be cleaned and extended with
 * special content if there is $, which serves as sign for var-start
 */


/**
 * @brief function that deletes part after $ from value
 * as it could not be verified as variable of envp
 * 
 * @param value_old	the value of the command line input token that has
 * to be adapted
 * @param wrongenvp not matching envp variable name, starting with $
 */
char	*delete_varname_from_value(char *value_old, char *wrongenvp)
{
	int		i;
	char	*value_new;
	char	*temp;

	i = 0;
	temp = value_old;
	printf("test 3A: value_old: %s\nwrongenvp: %s\n", value_old, wrongenvp);
	i = (ft_strlen(value_old) - ft_strlen(wrongenvp));
	value_new = ft_calloc((i + 1), sizeof(char));
	// printf("calloc: %i\n", (i + 1));
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
	// printf("test 4B value_new: %s\n", value_new);
	return (value_new);
}

/**
 * @brief function that adds required envp-variable to value
 * 
 * 2 options
 * (1) overwrite the former value of command input token (and remalloc before)
 * (2) create new string, free old string and set new string to node of linked list with tokens as new value
 * 
 * @param value_old	the value of the command line input token that has
 * to be adapted
 * @param env	value of env variable
 * @param env_name env variable name, starting with $
 */
char	*add_env_to_value(char *value_old, char *env, char *env_name)
{
	char	*value_new;
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
	// printf("test 3A: %s\nvalue_old: %s\n", (env), value_old);
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
	// printf("test 4A\n");
	return (value_new);
}

/**
 * @brief function that checks if the &keywords is part of envp
 * 
 * @param value_old the value of the command line input token that has
 * to be adapted
 * @param var_name potential env variable name, starting with $
 * @param env 
 */
static char	*ft_var_envchecker(char *value_old, char *var_name, char **env)
{
	// printf("env variable name: %s\nlength: %zu\n", (var_name + 1), ft_strlen(var_name + 1));
	while (env && *env)
	{
		// printf("test 2A: %s\n", *env);
		if (!ft_strncmp(*env, (var_name + 1), ft_strlen(var_name + 1)))
		{
			return (add_env_to_value(value_old, (*env + (ft_strlen(var_name + 1) + 1)), var_name));
		}
		env++;
	}
	// printf("test2B\n");
	return (delete_varname_from_value(value_old, var_name));
	
}

/**
 * @brief function that extends the tokens' value with env infos
 * by searching for 1st occurance of $ and the following variable name,
 * than sending this to ft_extender
 * 
 * @param value_old the value of the command line input token that has
 * to be adapted
 * @param env the environment variables of minishell that have to be checked for
 */
static char	*ft_var_creator(char *value_old, char **env)
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
					&& !((value_old[i] >= 9 && value_old[i] <= 13)
					|| (value_old[i] == ' ')
					|| !(ft_isalnum(value_old[i]))))
					i++;
			temp = ft_substr(value_old, k, (i - k));
			// printf("Variable name to search for: %s\n", temp);
			if (!temp)
				error_handling(2);
			value_new = ft_var_envchecker(value_old, temp, env);
			free(temp);
			// printf("test 5\n");
			return (value_new);
		}
		i++;
	}
	return (value_old);
}

/**
 * @brief function that expands the tokens' value with pid infos
 * 
 * @param 
char	*ft_pid_expander(((char *)curr->content)->value)
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
 * @brief recursive function to transform a number to a string
 * 
 * @param charnbr the string to integrate the number in
 * @param nbr the int to integrate
 * @param count	the index at which point to integrate nbr in
 */
void	ft_create_nbr(char *charnbr, int nbr, int count)
{
	if (nbr > 9)
	{
		charnbr[count] = (nbr % 10) + '0';
		ft_create_nbr ((charnbr), (nbr / 10), (count - 1));
	}
	else
		charnbr[count] = (nbr % 10) + '0';
}

/**
 * @brief helper function for ft_givenbr to count length of
 * nbr to be able to malloc a char
 * 
 * @param nbr the int to count in
 */
int	ft_count_nbr(int nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
		count += 1;
	while (nbr != 0)
	{
		nbr /= 10;
		count += 1;
	}
	return (count);

}

/**
 * @brief helper function to transform a number in char* and return it
 * 
 * @param nbr the number to transform from
 */
static char	*ft_givenbr(int nbr)
{
	char	*charnbr;
	int		count;
	int		i;

	count = 0;
	charnbr = NULL;
	i = 0;
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	else
	{
		count = ft_count_nbr(nbr);
		charnbr = ft_calloc((count + 1), sizeof(char));
		ft_printf("count no: %i\n", count);
		if (!charnbr)
			error_handling(2);
		if (nbr < 0)
		{
			charnbr[i] = '-';
			i += 1;
			nbr *= (-1);
		}
		if (nbr > 9)
			ft_create_nbr(charnbr, nbr, (count - 1));
		else
			charnbr[i] = nbr + '0';
		charnbr[count] = '\0';
		return (charnbr);
	}
}

/**
 * @brief function that extends the tokens' value with exit_code infos
 * 
 * @param value_old the tokens value that has to be adapted
 * @param exit_code the value that has to be inserted
 */
static char	*ft_exit_expander(char *value_old, int exit_code)
{
	char	*value_new;
	char	*value_old_save;
	char	*exit_code_input;
	char	*exit_code_input_save;
	int		i;

	i = 0;
	value_old_save = value_old;
	exit_code_input = ft_givenbr(exit_code);
	exit_code_input_save = exit_code_input;
	value_new = ft_calloc((ft_strlen(exit_code_input) + ft_strlen(value_old) + 1), sizeof(char));
	// if (exit_code_input[0] == '0')
	// {
		while (*value_old && 
			!(*value_old == '$' && *(value_old + 1) == '?'))
		{
			value_new[i] = *value_old;
			i += 1;
			value_old += 1;
		}
		while(*exit_code_input)
		{
			value_new[i] = *exit_code_input;
			i += 1;
			exit_code_input += 1;
		}
		value_old += 2;
		while (*value_old)
		{
			value_new[i] = *value_old;
			i += 1;
			value_old += 1;
		}
		value_new[i] = '\0';
		free(exit_code_input_save);
		return (value_new);
	// }
	// else
	// {
		// free(value_new);
		// free(exit_code_input_save);
		// return (ft_strdup(value_old_save));
	// }
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
 * @param token node of token-list that has to be cleaned from quotes
 * @param big structure which contains the environmental variable array
 */
static void	ft_var_checker(void	**token, t_big *big)
{
	t_lexer	*temp;
	char	*value_new;
	char	*value_old;
	int		i;

	i = 0;
	temp = *token;
	value_new = NULL;
	value_old = temp->value;
	while (value_old[i])
	{
		if (value_old[i] == '$' && value_old[i + 1] == '?')
		{
			value_new = ft_exit_expander(value_old, big->exit_code);
			temp->value = value_new;
			// printf("test 6: %s\n", (temp->value));
			free (value_old);
			value_old = NULL;
			value_old = temp->value;
		}
		else if (value_old[i] == '$')
		{
			value_new = ft_var_creator(value_old, big->env);
			temp->value = value_new;
			// printf("test 6: %s\n", (temp->value));
			free (value_old);
			value_old = NULL;
			value_old = temp->value;
		}
		if (value_old[i])
			i += 1;
	}
}

/**
 * @brief this functions deletes quotation marks at the beginning and end of
 * the value of token single_quoted / double_quoted
 * 
 * DO I HAVE TO ENSURE THAT value_old has enough characters to remove quotes?
 * 
 * @param token node of token-list that has to be cleaned from quotes
 */
static void	ft_quote_remover(void **token)
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
	// printf ("Calloc: %lu, real: %zu\n",
		// ((ft_strlen(value_old) - 2)), ft_strlen(value_new));
	free(value_old);
}

/**
 * @brief function that organises the expansion and reduction
 * of command line input by checking for specific string tokens
 * 
 * MISSING, if we want to handle UNCLOSED QUOTES: delete them
 * 
 * @param lexx linked list with cleaned command line input and tokens
 * @param big structure which contains the environmental variable array
 */
void	ft_expa_precond(t_list *lexx, t_big *big)
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
			// printf("test 7: %s\n", (((t_lexer *)curr->content)->value));
		}
		curr = curr->next;
	}
}
