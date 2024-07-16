/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:45:33 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/16 11:06:11 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* NAME: size-bounded string copying and concatenation */
/* DESCRIPTION: */
/* The strlcat() function appends the NUL-terminated */
/* string src to the end of dst. It will append */
/* at most size - strlen(dst) - 1 bytes, */
/* NUL-terminating the result. */
/* Note that a byte for the NUL should be included in size, */
/* both src and dst must be NUL-terminated */
/* RETURN VALUE: */
/* The and strlcat() function return the total length */
/* of the string it tried to create. That means the initial */
/* length of dst plus the length of src.  While this may seem */
/* somewhat confusing, it was done to make truncation detection simple. */
/* ONLY FOR TESTING PURPOSE: */
/* !!!use -lbsd for compiling!!! */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendest;
	size_t	j;

	lendest = ft_strlen(dst);
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	else if (size <= lendest)
		return (size + ft_strlen(src));
	else
	{
		while (src[j] && j < (size - lendest - 1))
		{
			dst[lendest + j] = src[j];
			j++;
		}
		dst[lendest + j] = '\0';
	}
	while (src[j])
		j++;
	return (lendest + j);
}
/*
#include <bsd/string.h>
int	main(void)
{
	char	dst[30] = "hal45i";
	char	dst2[30] = "hal45i";
	char	src[] = "halli0789n";
	int	size;
//	unsigned int	out;
	
	size = 12;
//	out = ft_strlcat(dst, src, size);
	printf("dest (me): %s\nreturn", dst);
	printf("(strlcat me): %zu\n", ft_strlcat(dst, src, size));
	printf("dest (ex): %s\nreturn(strlcat ex): ", dst2);
	printf("%zu\n", strlcat(dst2, src, size));
	return (0);
}
*/
