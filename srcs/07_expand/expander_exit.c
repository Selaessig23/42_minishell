/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:21:45 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 14:21:48 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be extended with
 * content exit status of last command executed in minishell
 * (0 if there is no last command)
 */

/**
 * @brief helper function for ft_exit_expander 
 * that integrates the exit status to new string
 * and returns the counter i to be able to proceed with
 * reading in ft_exit_expander
 * 
 * @param i	the counter that has to be continued
 * @param value_new the tokens value that has to be adapted
 * @param exit_code_input the value that has to be inserted
 */
static int	ft_add_exit_status(int i, char *value_new, char *exit_code_input)
{
	char	*temp;

	temp = value_new;
	while (*exit_code_input)
	{
		*temp = *exit_code_input;
		i += 1;
		exit_code_input += 1;
		temp += 1;
	}
	return (i);
}

/**
 * @brief function that extends the tokens' value with exit_code infos
 * 
 * @param value_new the variable to write in the new value
 * @param value_old the tokens value that has to be adapted
 * @param exit_code_input the value that has to be inserted
 */
char	*ft_exitcode_copier(char *value_new, 
			char *value_old, char *exit_code_input)
{
	int		i;

	i = 0;
	while (*value_old && 
		!(*value_old == '$' && *(value_old + 1) == '?'))
	{
		value_new[i] = *value_old;
		i += 1;
		value_old += 1;
	}
	i = ft_add_exit_status(i, &value_new[i], exit_code_input);
	value_old += 2;
	while (*value_old)
	{
		value_new[i] = *value_old;
		i += 1;
		value_old += 1;
	}
	value_new[i] = '\0';
	return (value_new);
}

/**
 * @brief function that allocates space for a new variable 
 * value_new which should include the exit code information
 * 
 * @param value_old the tokens value that has to be adapted
 * @param exit_code the value that has to be inserted
 */
char	*ft_exit_expander(char *value_old, int exit_code)
{
	char	*value_new;
	char	*exit_code_input;

	exit_code_input = ft_givenbr(exit_code);
	value_new = ft_calloc((ft_strlen(exit_code_input) 
				+ ft_strlen(value_old) + 1), sizeof(char));
	value_new = ft_exitcode_copier(value_new, value_old, exit_code_input);
	free(exit_code_input);
	exit_code_input = NULL;
	return (value_new);
}
