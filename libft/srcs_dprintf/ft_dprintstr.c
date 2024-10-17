/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:10:40 by mstracke          #+#    #+#             */
/*   Updated: 2024/01/22 17:11:00 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintstring(va_list args)
{
	char	*help;

	help = va_arg(args, char *);
	if (help == NULL)
	{
		ft_putstr_fd("(null)", 2);
		return (6);
	}
	else
	{
		ft_putstr_fd(help, 2);
		return (ft_strlen(help));
	}
}
