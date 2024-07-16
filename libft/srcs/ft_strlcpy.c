/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:16:57 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/16 11:01:31 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* DESCRIPTION: */
/* The strlcpy() and strlcat() functions copy and concatenate */ 
/* strings respectively. They are designed to be safer, */
/* more consistent, and less error prone replacements for */
/* strncpy(3) and strncat(3). Unlike those functions, */
/* strlcpy() and strlcat() take the full size of the buffer */
/* (not just the length) and guarantee to NUL-terminate the */
/* result (as long as size is larger than 0). */
/* src must be NUL-terminated */
/* The strlcpy() function copies up to size - 1 characters */
/* from the NUL-terminated string src to */
/* dst, NUL-terminating the result.*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
