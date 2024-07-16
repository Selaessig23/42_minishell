/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:12:57 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/17 11:52:54 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*NAME: zero a byte string */
/*DESCRIPTION: erases the data in the n bytes */
/* of the memory starting at the location pointed to by s, */
/* by writing zeros (bytes containing '\0') to that area. */
#include "libft.h"

#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*help;
	size_t			i;

	help = s;
	i = 0;
	while ((n - i) > 0)
	{
		help[i] = '\0';
		i++;
	}
}
/*
void	ft_putchar(char c)
{	
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	main(void)
{
	char	str[] = "wonderfool";
	char	test[] = "wonderfool";
//	why does this not work? segmentation fault
//	char	*str = "wonderfool";
//
	char	*s;
	size_t	n;

	//core dumped (segmentation fault) with more than 20)
	n = 20;
	s = &str[3];
	//n = ft_strlen(s);
	ft_bzero(s, n);
	ft_putstr(str);
	ft_putchar(10);
	s = &test[3];	
	bzero(s, n);
	ft_putstr(test);
	ft_putchar(10);
	
	return (0);
}
*/
