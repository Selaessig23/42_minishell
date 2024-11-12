/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:49:10 by mstracke          #+#    #+#             */
/*   Updated: 2024/11/12 14:49:12 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * DESRIPTION: 
 * in this file specific several helper functions for the
 * expander-part of minishell are collected
 */

/**
 * @brief helper function for ft_env_varname_creator in expander_env.c
 * that checks for characters that are defined to be part of
 * the var_name within (beginning og) the env-variable-value
 * 
 * @param c the character that has to be checked
*/
int	ft_is_env_var(char c)
{
	if ((c >= 'A' && c <= 'Z')
		|| c == '_'
		|| ft_isdigit(c))
		return (1);
	else
		return (0);
}

/**
 * @brief recursive (helper) function for ft_givenbr
 * to transform a number to a string
 * 
 * @param charnbr the string to integrate the number in
 * @param nbr the int to integrate
 * @param count	the index at which point to integrate nbr in
 */
static void	ft_create_nbr(char *charnbr, int nbr, int count)
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
static int	ft_count_nbr(int nbr)
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
 * @brief function to transform a number in char* and return it
 * 
 * @param nbr the number to transform from
 */
char	*ft_givenbr(int nbr)
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
		if (!charnbr)
			error_handling(2);
		if (nbr < 0)
		{
			charnbr[i] = '-';
			i += 1;
			nbr *= (-1);
		}
		ft_create_nbr(charnbr, nbr, (count - 1));
		charnbr[count] = '\0';
		return (charnbr);
	}
}
