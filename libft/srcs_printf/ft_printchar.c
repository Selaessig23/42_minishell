/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:20:22 by mstracke          #+#    #+#             */
/*   Updated: 2024/01/18 13:21:22 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(va_list args)
{
	char	help;

	help = va_arg(args, int);
	ft_putchar_fd(help, 1);
	return (1);
}
