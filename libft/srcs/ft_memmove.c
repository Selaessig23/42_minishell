/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:32:38 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/23 13:40:56 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*DESCRIPTION */
/*The  memmove()  function  copies n bytes from memory area */
/*src to memory area dest. */
/*The memory areas may overlap: copying takes place as though */
/*the bytes in src are first copied into a temporary array that */
/*does not overlap src or dest, and the bytes are then copied */
/*from the temporary array to dest. */
/*RETURN VALUE */
/*The memmove() function returns a pointer to dest. */
/*UNDERSTANDING */
/*copy memory area, memory areas may overlap */
/*(which is main difference to memcpy) */
/*Memory: | A | B | C | D | E | F | */
/*Let's say we have a memmove operation where */
/*we want to copy three bytes from position A to position C. */
/*In this case, src points to the beginning of the data to be copied (A), */
/*and dest points to the destination position (C). */
/*There would be an overlap if we copy with memcpy. */
/*Memory: | A | B | A | B | A | F | */
/*instead of Memory: | A | B | A | B | C | F | */
/*to generally check if there is an overlapping: */
/*"if d+n < s || d >= s + n" */
/*It seems as if memmove can also cause overlapping. */
/*But by using a temporary variable the original */
/*values are preserved before copying them. */

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	d = dest;
	s = src;
	if (dest == NULL && src == NULL)
		return (0);
	if (d <= s)
		return (ft_memcpy(dest, src, n));
	else
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return ((void *)d);
}

/*
int	main(void)
{
//	const char	str1[] = "hey how are you today";
	char	str1[] = "lorem ipsum dolor sit amet";
	char	str2[] = "lorem ipsum dolor sit amet";
//	const char	str2[] = "hey how are you today";
//	const char	*str2;
	char	*dest1;
	char	*dest2;
//	char	dest2[7];
	size_t	n;
//	void	*r;
	void	*t1;
	void	*t2;

	//n = 15;
	dest1 = str1 - 4;
	dest2 = str1 - 4;	
//	n = ft_strlen(str1);
	n = 8;
	t1 = ft_memmove(dest1, str1, n);
	printf("Void r after ft_memmove: %p\n", t1);
	printf("Void dest after ft_memmove: %s\n", dest1);
//	printf("Void dest before MEMMOVE (ex): %s\n", dest1);
	t2 = memmove(dest2, str2, n);
	printf("Void r after MEMMOVE (ex): %p\n", t2);
	printf("Void dest after MEMMOVE (ex): %s\n", dest2);
	return (0);
}
*/
