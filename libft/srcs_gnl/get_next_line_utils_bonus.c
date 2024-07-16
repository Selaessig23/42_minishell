/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:00:00 by mstracke          #+#    #+#             */
/*   Updated: 2024/03/06 12:35:35 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//ft_calloc commented out because of duplicate in libft
/*
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*help;
	void			*r;
	size_t			i;

	i = 0;
	r = malloc (size * nmemb);
	help = r;
	if (!r)
		return (0);
	while (i < (nmemb * size))
	{
		help[i] = 0;
		i++;
	}
	return (r);
}
*/

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
		return (ft_calloc(1, sizeof(char)));
	if ((len) > (ft_strlen(s) - start))
		len = ((size_t)(ft_strlen(s) - start));
	r = malloc((len + 1) * sizeof(char));
	if (!r)
		return (0);
	ft_strncpy(r, &s[start], len);
	return (r);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	len;
	int		i;
	int		n; 

	i = 0;
	n = 0;
	len = (ft_strlen(s1)) + (ft_strlen(s2));
	if (len == 0)
		r = ft_calloc(1, sizeof(char));
	else 
	{
		r = (char *)malloc(sizeof(char) * (len + 1));
		if (!r)
			return (0);
		r = ft_strncpy(r, s1, ft_strlen(s1));
		n = ft_strlen(r);
		while (s2[i])
		{
			r[n + i] = s2[i];
			i++;
		}
		r[n + i] = '\0';
	}
	return (r);
}
