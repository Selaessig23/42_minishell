/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:32:18 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/21 15:21:43 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NAME: Compare memory areas */
/* DESCRIPTION: */
/* The  memcmp()  function  compares the first n bytes */
/* (each interpreted as unsigned char) of the */
/* memory areas s1 and s2. */
/* RETURN VALUE: */
/* The memcmp() function returns an integer less than, */
/* equal to, or  greater  than  zero  if  the first  n bytes */
/* of s1 is found, respectively, to be less than, to match, */
/* or be greater than the first n bytes of s2. */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = s1;
	str2 = s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	const char	s1[] = "";
	const char	s2[] = "hallo";
	size_t	n;
	int	r;

	n = ft_strlen(s1);
	//n = 5;
	r = ft_memcmp(s1, s2, n);
	printf("result: %i\n", r);
	r = 0;
	r = memcmp(s1, s2, n);
	printf("result: %i\n", r);
	return (0);
}
*/
