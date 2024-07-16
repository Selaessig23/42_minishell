/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:31:20 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/15 14:36:28 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* NAME: locate character in string */
/* DESCRIPTION: */
/* The strrchr() function returns a pointer */
/* to the last occurrence of the character c */
/* in the string s. */
/* RETURN VALUE: */
/* The strchr() and strrchr() functions return a pointer */
/* to the matched character or NULL if  the */
/* character  is  not found.  The terminating null byte */
/* is considered part of the string, so that */
/* if c is specified as '\0', these functions */
/* return a pointer to the terminator. */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i > 0 && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}
/*
int	main(void)
{
	char s[] = "hallap";
	char	*dest;
	int	c;
	
	c = 'h';
	dest = ft_strrchr(s, c);
	printf("Pointer to: %s\n", dest);
	return (0);
}
*/
