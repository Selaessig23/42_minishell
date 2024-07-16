/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:25:03 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/15 14:30:20 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* DESCRIPTION: */
/* The  strchr() function returns a pointer  */
/* to the first occurrence of the character c */
/* in the string s. */
/* RETURN VALUE: */
/* The strchr() and strrchr() functions return a pointer */
/* to the matched character or NULL if  the */
/* character  is  not found.  The terminating null byte */
/* is considered part of the string, so that */
/* if c is specified as '\0', these functions */
/* return a pointer to the terminator. */
char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
/*
int	main(void)
{
	char s[] = "hallap";
	char	*dest;
	int	c;
	
	c = 't';
	dest = ft_strchr(s, c);
	printf("Pointer to: %s\n", dest);
	return (0);
}
*/
