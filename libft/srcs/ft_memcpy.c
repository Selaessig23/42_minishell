/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:23:46 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/21 13:40:25 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*copy memory area, memory area must not overlap */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*temp;
	unsigned char		*help;
	size_t				i;

	help = dest;
	temp = src;
	i = 0;
	if (!help && !temp)
		return (dest);
	while (i < n)
	{
		help[i] = temp[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	const char	str[] = "hey how are you today";
	char	dest1[20];
//	char	dest2[20];
	size_t	n;
//	void	*r;
	void	*t;

	//n = 15;
	n = ft_strlen(str);
	t = ft_memcpy(dest1, str, n);
	printf("Void r after ft_memcpy: %p\n", t);
	printf("Void dest after ft_memcpy: %s\n", dest1);
//	r = NULL;
	t = memcpy(dest1, str, n);
	printf("Void r after MEMCPY (ex): %p\n", t);
	printf("Void dest after MEMCPY (ex): %s\n", dest1);
}
*/
