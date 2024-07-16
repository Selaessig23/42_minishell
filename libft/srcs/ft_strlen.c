/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:31:44 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/23 12:00:40 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
int	main(void)
{
	char	*s = "Hallo";
	size_t	r;

	r = ft_strlen(s);
	printf("Result for strlen: %zu", r);
	return (0);
}
*/
