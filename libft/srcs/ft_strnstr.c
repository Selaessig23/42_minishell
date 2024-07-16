/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:55:46 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/16 13:13:51 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* NAME: locate a substring in a string */
/* The strnstr() function locates the first occurrence */ 
/* of the null-terminated string little in the */
/* string big, where not more than len characters are searched. */
/* Characters that appear after a ‘\0’ character are not searched. */
/* Since the strnstr() function is a FreeBSD specific API, it */
/* should only be used when portability is not a concern. */
/* RETURN VALUES: */
/* If little is an empty string, big is returned; */
/* if little occurs nowhere in big, NULL is returned; */
/* otherwise a pointer to the first character of the */
/* first occurrence of little is returned. */
/* TESTING: fix printf in main, had to shorten for norminette */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_strlen(little) > 0)
	{
		while (big[i] && ((i + ft_strlen(little)) <= n))
		{
			if (ft_strncmp(&(big[i]), little, ft_strlen(little)) == 0)
				return ((char *)&big[i]);
			i++;
		}
		return (0);
	}
	else
		return ((char *)big);
}
/*
int	main(void)
{
	const char	*big = "Hallo Halli Hallabi";
//	const char	*big = "lorem ipsum dolor sit amet"; //testcase 2
//	const char	*big = "";
//	const char	*big = "0";
//	const char	*little = "0";
	const char	*little = "dolor";
//	const char	*little = "";
	char	*dst;
	char	*tst;
	size_t	n;
	
	n = 25;
//	n = 15; //testcase 2
	dst = (ft_strnstr(big, little, n));
	//no chance to test with strnstr, I always receive
	//error messages "inplicit declaration of strnsr is implicit
	tst = (strstr(big, little));
	printf("Result for n me = %zu\nResult for 
	dest me = %s\nResult for dest ex = %s\n", n, dst, tst);
	return (0);
}
*/
