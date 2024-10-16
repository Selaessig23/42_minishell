/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint_uint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:23:44 by mstracke          #+#    #+#             */
/*   Updated: 2024/01/18 13:25:37 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprintint(va_list args)
{
	int	help;
	int	count;

	count = 0;
	help = va_arg(args, int);
	ft_putnbr_fd(help, 2);
	if (help <= 0)
		count++;
	while (help != 0)
	{
		help /= 10;
		count++;
	}
	return (count);
}
