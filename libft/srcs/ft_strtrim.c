/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:27:18 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/27 09:50:59 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* DESCRIPTION:*/
/* Allocates (with malloc(3)) and returns a copy of ’s1’*/
/* with the characters(!, not whole string in total))*/
/*   specified in ’set’ removed */
/* from the beginning and the end of the string.*/
/* RETURN VALUE: The trimmed string. NULL if the allocation fails */

/* function to check the char at beginning and */
/* end of s1 for chars mentioned in set */
static int	ft_checkstr(char const s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	i;
	int		p;

	i = 0;
	if (!s1)
		p = 0;
	else
		p = (ft_strlen(s1) - 1);
	while (s1[i] && ft_checkstr(s1[i], set) == 1)
		i++;
	if ((i) == ft_strlen(s1) || p == 0)
		dest = ft_strdup("");
	else
	{
		while (p >= 0 && ft_checkstr(s1[p], set) == 1)
			p--;
		dest = ft_substr(s1, i, ((p + 1) - i));
	}
	return (dest);
}
/*
int	main(void)
{
	char	*dest;
//	char const	s1[] = "ooooohhh %my cute cats% hallo";
//	char const	set[] = "lloh";
//	char const	s1[] = "lorem \n ipsum \t dolor \n sit \t amet";
//	char const	set[] = " ";
//	char const	s1[] = "lorem ipsum dolor sit amet";
//	char const	set[] = "te";
	//test4
//	char const	s1[] = "   xxx   xxx";
//	char const	set[] = " x";
	dest = ft_strtrim(s1, set);
	printf("Print dest:%s\n", dest);
	return (0);
}
*/
