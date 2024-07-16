/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:32:17 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/20 14:36:55 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* NAME: scan memory for a character */
/* DESCRIPTION: */
/* The  memchr() function scans the initial n bytes */
/* of the memory area pointed to by s for the */
/* first instance of c. Both c and the bytes of the memory */
/* area pointed to by s are interpreted as unsigned char. */
/* RETURN VALUE: */
/* The memchr() and memrchr() functions return */
/* a pointer to the matching byte or NULL if the */
/* character does not occur in the given memory area. */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*help;
	size_t				i;

	help = s;
	i = 0;
	while (i < n)
	{
		if (help[i] == (unsigned char)c)
			return ((void *) &help[i]);
		else
			i++;
	}
	return (0);
}
