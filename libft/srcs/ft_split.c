/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:43:23 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/16 10:40:19 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*DESCRIPTION: */
/*Allocates (with malloc(3)) and returns an array */
/*of strings obtained by splitting ’s’ using the */
/*character ’c’ as a delimiter. The array must end */
/*with a NULL pointer. */
/*RETURN VALUE: */
/* The array of new strings resulting from the split. */
/*NULL if the allocation fails. */
static void	*ft_free_i(char **dest, int arrno)
{
	int	i;

	i = 0;
	while (i <= arrno)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return (0);
}

static char	**ft_strcut(char **dest, const char *s, char c, size_t i)
{
	size_t	a;
	size_t	p;

	a = 0;
	p = i;
	while (s[i])
	{
		if (s[i] == c || ((i == ft_strlen(s) - 1) && s[i] != c))
		{
			if ((i == ft_strlen(s) - 1) && s[i] != c)
				dest[a] = ft_substr(s, p, (i + 1 - p));
			else
				dest[a] = ft_substr(s, p, (i - p));
			if (!(dest[a]))
				return (ft_free_i(dest, a));
			while (s[i + 1] == c)
				i++;
			p = i + 1;
			a++;
		}
		i++;
	}
	dest[a] = NULL;
	return (dest);
}

/* this function counts occurance of c in s */
/* respecitive how many words have to been created */
static size_t	ft_amc(size_t i, const char *s, char c)
{
	size_t	amountc;

	amountc = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			amountc++;
			while (s[i + 1] == c)
				i++;
		}
		i++;
	}
	if (s[i - 1] != c)
		return (amountc + 1);
	else
		return (amountc);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	len;
	size_t	i;

	i = 0;
	while (s[i] == c)
		i++;
	if (ft_strncmp(s, "", 1) == 0)
	{
		dest = ft_calloc(1, sizeof(char *));
		if (!dest)
			return (NULL);
	}
	else
	{
		len = ft_amc(i, s, c);
		dest = ft_calloc((len + 1), sizeof(char *));
		if (!dest)
			return (NULL);
		dest = ft_strcut(dest, s, c, i);
	}
	return (dest);
}
/*
int	main(void)
{
//	char	s[] = "that is a long lasting story ";
//	char	s[] = "   lorem   ipsum dolor     
	//	sit amet, consectetur   adipiscing elit. Sed non risus. Suspendisse   ";
	// char	s[] = "";
	// char	c;
	// char	**dest;
	int		i;
	//char *s = "      split       this for   me  !       ";
	char *s = "hello!";
 	char **dest = ft_split(s, ' ');
	// c = ' ';
	// c = 'z';
	// dest = ft_split(s, c);
	i = 0;
	while (dest[i])
		{
			printf("Result for ft_split: $%s$\n", dest[i]);
			i++;
		}
		i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return (0);
	//split-function here
	// ft_free (dest);
}
*/
