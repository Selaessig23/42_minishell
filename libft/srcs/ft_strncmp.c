/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:42:38 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/16 11:45:22 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
int	main(void)
{
//	char	*s1 = "ABZAs1sAs";
//	"\200" = octal200 (== 128 in ASCII)
	char	*s1 = "test\202";
//	char	*s2 = "ABZAs1sAsA";
//	"\0" = null terminator
	char	*s2 = "test\0";
	unsigned int	n;
	int	r;
	
	n = 6;	
	r = ft_strncmp (s1, s2, n);
	printf("Result_me = %i\n", r);
	printf("Result_ex = %d\n", strncmp(s1, s2, n));
	return (0);
}
*/
