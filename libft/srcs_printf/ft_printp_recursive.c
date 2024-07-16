/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp_recursive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:59:37 by mstracke          #+#    #+#             */
/*   Updated: 2024/01/22 15:59:43 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_countp(size_t help)
{
	int	i;

	i = 0;
	if (help == 0)
		i++;
	else
	{
		while (help != 0)
		{
			help /= 16;
			i++;
		}
	}
	return (i);
}

static void	ft_writep(size_t help, char *hex)
{
	if (help > 15)
	{
		ft_writep((help / 16), hex);
		ft_putchar_fd(hex[help % 16], 1);
	}
	else
		ft_putchar_fd(hex[help], 1);
}

int	ft_printpointer(va_list args, char *hex)
{
	size_t			help;

	help = va_arg(args, size_t);
	if (help == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd ("0x", 1);
	ft_writep(help, hex);
	return (ft_countp(help) + 2);
}
