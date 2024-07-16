/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:22:43 by mstracke          #+#    #+#             */
/*   Updated: 2024/01/17 13:53:16 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to avoid duplications
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

//printf functions
int		ft_printf(const char *format, ...);
int		ft_printui(va_list args);
int		ft_printint(va_list args);
int		ft_printhexa(va_list args, char *c);
int		ft_printpointer(va_list args, char *c);
int		ft_printstring(va_list args);
int		ft_printchar(va_list args);

#endif
