/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:29:49 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/16 19:52:33 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last_char(const char *str, char c)
{
	size_t len;

	len = 0;
    if (!str || *str == '\0')
	{ // Check if string is NULL or empty
        return (0);
    }
    len = strlen(str); // Get the length of the string
    if (str[len - 1] == c)
	{ // Compare the last character
        return (1);
    } else
	{
        return (0);
    }
}

int	is_exact_string(const char *str_org,char *str_cmp)
{
	if (!ft_strncmp(str_org, str_cmp, ft_strlen(str_org)) 
		&& ft_strlen(str_org) == ft_strlen(str_cmp))
		return (1);
	else
		return (0);
}
