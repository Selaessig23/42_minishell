/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:13:03 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/28 13:28:30 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* DESCRIPTION
 * Applies the function ’f’ to each character of the
 * string ’s’, and passing its index as first argument
 * to create a new string (with malloc(3)) resulting
 * from successive applications of ’f’.
 * RETURN VALUE:
 * The string created from the successive applications 
 * of ’f’. Returns NULL if the allocation fails. */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	dest = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (s[i])
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
static char	ft_revalp(unsigned int i, char c)
{
	c = 'z' - i;
	return (c);
}

int	main(void)
{
//	char	s[] = "hallo";
	char	s[] = "trellossss";
	char	*dest;

	dest = ft_strmapi(s, ft_revalp);
	printf("$%s$\n", dest);
	return (0);
}
*/
