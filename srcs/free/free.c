/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:34:39 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/18 19:35:33 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to clean t_big struct.
*/
void	free_t_big(t_big *big)
{
	if (big->env)
		ft_free(big->env);
	if (big->cmdlist)
		ft_free_cl(&(big->cmdlist));
	if (big->binarypaths)
		ft_free(big->binarypaths);
	free(big);
	big = NULL;
}
