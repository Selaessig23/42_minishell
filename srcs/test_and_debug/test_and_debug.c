/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_and_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:37:11 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 19:37:25 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Temporary function to display what t_big holds.
void	printf_env(t_big *big)
{
	int	i;

	i = 0;
	while (big->env[i])
	{
		ft_printf("big->env[%i]:\n%s\n", i, big->env[i]);
		i++;
	}
	ft_printf("big->env[%i]:\n%s\n", i, big->env[i]);
}