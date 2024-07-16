/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:17:17 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/22 14:20:17 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* TITLE: Duplicate a string */
/* DESCRIPTION: */
/* The  strdup() function returns a pointer */
/* to a new string which is a duplicate of the string s. */
/* Memory for the new string is obtained with malloc, */
/* and can be freed with free. Library string.h is required. */
/* On success, the strdup() function returns a pointer */
/* to the duplicated string. It returns NULL if insufficient */
/* memory was available, with errno set to */
/* indicate the cause of the error. */
static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = ft_strlen(s);
	dest = malloc((i + 1) * sizeof(char));
	if (!dest)
		return (0);
	dest = ft_strcpy(dest, s);
	return (dest);
}
/*
int	main(void)
{
	//char	str[] = "hallodrio";
	char	str[] = " ";
	char	*dest1;
	char	*dest2;

	dest1 = ft_strdup(str);
	printf("Result for dest (me): %s\n", dest1);
	printf("Size of dest (me): %zu\n", ft_strlen(dest1));
	dest2 = strdup(str);
	printf("Result for dest (ex): %s\n", dest2);
	printf("Size of dest (me): %zu", ft_strlen(dest2));
	return (0);
}
*/
