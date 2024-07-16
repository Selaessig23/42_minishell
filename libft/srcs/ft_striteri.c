/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:30:07 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/28 13:40:48 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*DESCRIPTION: 
 * Applies the function ’f’ on each character of 
 * the string passed as argument, passing its index 
 * as first argument. Each character is passed by 
 * address to ’f’ to be modified if necessary.
 * RETURN VALUE: NONE
 */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
