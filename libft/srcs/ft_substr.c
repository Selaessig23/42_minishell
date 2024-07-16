/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:13:17 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/22 15:43:03 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*ft_substr */
/* description: Allocates (with malloc(3)) and returns a substring */
/* from the string ’s’. The substring begins at index ’start’ and is of */
/* maximum size ’len’. */
static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;

	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if ((len) > (ft_strlen(s) - start))
		len = ((size_t)(ft_strlen(s) - start));
	r = malloc((len + 1) * sizeof(char));
	if (!r)
		return (0);
	ft_strncpy(r, &s[start], len);
	return (r);
}
/*
int	main(void)
{
//	char	s[] = "hallihalloyoufunnyrabbit";
//	char	s[] = "lorem ipsum dolor sit amet";
//	char	s[] = "hola";
//	char	s[] = "tripouille";
	char	s[] = "0123456789";
	unsigned int	start;
	size_t	len;
	char	*dest;

	start = 9;
	//start = 10;
	//start = 5;
	len = 10;
	//len = 5;
	dest = ft_substr(s, start, len);
	printf("Result for ft_substr: %s\n", dest);
	return (0);
}
*/
