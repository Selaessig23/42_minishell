/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:21:42 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/22 14:53:08 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* TITLE: Allocate and free dynamic memory */
/* ("contiguous allocation", instead of "memory allocation" for malloc) */
/* DESCRIPTION: The  calloc()  function allocates memory */
/* for an array of nmemb elements of size bytes each */
/* and returns a pointer to the allocated memory. */
/* The memory is set to zero */
/* (what is the main difference to malloc, which is uninitialized). */ 
/* Therefor calloc is slightly slower than malloc. */
/* But it can be more convenient when working with arrays */
/* where all elements should start with a known value (zero). */
/* If nmemb or size is 0, then  calloc()  returns  either NULL, */
/* or a unique pointer value that can later be successfully passed to free(). */
/* If the multiplication of nmemb and size would result */
/* in integer overflow, then calloc() returns an error. */
/* By contrast, an integer overflow would not be detected */
/* in the following call to malloc(), with the result that */
/* an incorrectly sized block of memory would be allocated: */
/* malloc(nmemb * size); */
/* LIBRARY: <stdlib.h> */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;

	r = malloc (size * nmemb);
	if (!r)
		return (0);
	ft_memset(r, 0, (nmemb * size));
	return (r);
}
