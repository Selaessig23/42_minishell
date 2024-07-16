/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:01:54 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/20 11:18:24 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NAME: fill memory with a constant byte */
/* DESCRIPTION: The memset() function fills the */
/* first n bytes of the memory area pointed to by s */
/* with the constant byte c. */
/* RETURN VALUE: The memset() function */
/* returns a pointer to the memory area s. */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*help;
	size_t			i;

	help = s;
	i = 0;
	while (i < n)
	{
		help[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/*
int	main(void)
{
//	int	array[] = {1, 2, 3, 4, 5};
	char	str[] = "hey how are you today";
//	why does this not work? segmentation fault
//	char	*str = "hey how are you today";

	char	*s;
	int	c;
	size_t	n;
	void	*e;
	
	s = &str[3];
	c = 97;
	n = 1;
	e = ft_memset(s, c, n);
	printf("Void s after function: %p\n", e);
	printf("string after function: %s\n", str);
	printf("[0] after function: %i\n", str[0]);
	printf("[1] after function: %i\n", str[1]);
	printf("[2] after function: %i\n", str[2]);
	printf("[3] after function: %i\n", str[3]);
	printf("[4] after function: %i\n\n\n", str[4]);
	e = memset(s, c, n);
	printf("Void s after function (ex): %p\n", e);
	printf("string after function (ex): %s\n", str);
	printf("[0] after function (ex): %i\n", str[0]);
	printf("[1] after function (ex): %i\n", str[1]);
	printf("[2] after function (ex): %i\n", str[2]);
	printf("[3] after function (ex): %i\n", str[3]);
	printf("[4] after function (ex): %i\n", str[4]);
	return (0);
}
*/
