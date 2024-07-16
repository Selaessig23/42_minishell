/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:58:42 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/23 12:02:04 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a new string, 
 * which is the result of the concatenation of ’s1’ and ’s2’.
 * Return value: The new string. NULL if the allocation fails.
 */
static char	*ft_strcat(char *dest, const char *s2)
{
	int	i;
	int	n; 

	i = 0;
	n = ft_strlen(dest);
	while (s2[i])
	{
		dest[n + i] = s2[i];
		i++;
	}
	dest[n + i] = '\0';
	return (dest);
}

static char	*ft_strcpy(char *dest, const char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	len;

	len = (ft_strlen(s1)) + (ft_strlen(s2));
	if (len == 0)
		r = ft_strdup("");
	else 
	{
		r = (char *)malloc(sizeof(char) * (len + 1));
		if (!r)
			return (0);
		r = ft_strcpy(r, s1);
		r = ft_strcat(r, s2);
	}
	return (r);
}
/*
int	main(void)
{
//	char	s1[] = "halli hallo you...\n";
//	char	s2[] = "... you funny rabbit";
//	char	s1[] = "\0";
	char	s2[] = "\0";
	char	s1[] = "lorem ipsum";
//	char	s2[] = "dolor sit amet";
	char	*dest;

	dest = ft_strjoin(s1, s2);
	printf("Result for ft_substr: %s\n", dest);
	return (0);
}
*/
