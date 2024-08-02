/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:04:46 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/16 10:05:09 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * counts an returns the size of an array of strings
 * 
 * @param arr_str the array of strings to count
 */
size_t	ft_arrlen(char **arr_str)
{
	size_t	i;

	i = 0;
	while (arr_str[i])
		i++;
	return (i);
}
