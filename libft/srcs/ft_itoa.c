/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:56:49 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/27 14:09:07 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* DESCRIPTION:*/
/* Allocates (with malloc(3)) and returns a string */
/* representing the integer received as an argument */
/* Negative numbers must be handled */
/* RETURN VALUE: */
/* The string representing the integer. */
/* NULL if the allocation fails. */

/*this function copies the int to the allocated char*, except '\0'*/
static char	*ft_cpynbr(char *dest, int n, int i)
{
	if (n < 0)
	{
		dest[0] = 45;
		n *= (-1);
	}
	if (n == 0)
		dest[0] = 0 + 48;
	if (n > 9)
	{
		dest[i] = ((n % 10) + 48);
		ft_cpynbr(dest, (n / 10), (i - 1));
	}
	else
		dest[i] = (n + 48);
	return (dest);
}

/*this function allocates the memory size for malloc*/
static int	ft_allochar(int n, int i)
{
	while (n / 10 != 0)
	{
		n = (n / 10);
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		s;
	int		i;

	if (n == -2147483648)
	{
		dest = ft_strdup("-2147483648\0");
		return (dest);
	}
	if (n < 0)
		s = 1;
	else 
		s = 0;
	i = ft_allochar(n, s);
	dest = malloc((i + 2) * sizeof(char));
	if (!dest)
		return (0);
	dest = ft_cpynbr(dest, n, i);
	dest[i + 1] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char	*dest = NULL;
	int		n;

	n = 0;
	dest = ft_itoa(n);
	printf("Argument: %s", dest);
	return (0);
}
*/
