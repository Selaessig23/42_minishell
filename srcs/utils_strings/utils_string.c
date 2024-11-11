/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:29:49 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/10 20:31:03 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exact_string(const char *str_org,char *str_cmp)
{
	if (!ft_strncmp(str_org, str_cmp, ft_strlen(str_org)) 
		&& ft_strlen(str_org) == ft_strlen(str_cmp))
		return (1);
	else
		return (0);
}
