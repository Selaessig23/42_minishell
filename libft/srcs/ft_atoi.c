/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:51:13 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/21 11:09:17 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NAME: convert a string to an integer */
/* DESCRIPTION: */
/* The atoi() function converts the initial portion */
/* of the string pointed to by nptr to int. */
/* RETURN VALUE: */
/* The converted value or 0 on error. */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	m;
	int	r;

	i = 0;
	m = 0;
	r = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			m++;
		i++;
	}
	while (ft_isdigit(nptr[i]) == 1)
	{
		r = (r * 10);
		r = r + (nptr[i] - 48);
		i++;
	}
	if (m % 2 != 0)
		r *= (-1);
	return (r);
}
/*
int	main(int argc, char **argv)
{
	int	r;
	
	if (argc == 2 && argv[1])
		r = ft_atoi(argv[1]);
	else
		r = 999;
	printf("result(me): %i\n", r);
	printf("result(ex): %i\n", atoi(argv[1]));
	return(0);
}
*/
