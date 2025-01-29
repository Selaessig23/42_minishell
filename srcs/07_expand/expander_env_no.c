/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env_no.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:37:36 by mstracke          #+#    #+#             */
/*   Updated: 2025/01/29 15:27:39 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific string-tokens will be reduced from
 *  $+varname as it does not match any env var name
 */

/**
 * @brief function that deletes part after $ (incl $) 
 * from value as it could not be verified as variable of envp
 * 
 * @param value_old	the value of the command line input token that has
 * to be adapted
 * @param wrongenvp not matching envp variable name, starting with $
 */
char	*delete_varname_from_value(char *value_old, char *wrongenvp)
{
	int		i;
	char	*value_new;

	i = 0;
	i = (ft_strlen(value_old) - ft_strlen(wrongenvp));
	value_new = ft_calloc((i + 1), sizeof(char));
	if (!value_new)
		error_and_exit(2);
	i = 0;
	while (value_old[i] && 
		(!ft_strnstr(&(value_old[i]), wrongenvp, ft_strlen(wrongenvp))))
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
	return (value_new);
}
