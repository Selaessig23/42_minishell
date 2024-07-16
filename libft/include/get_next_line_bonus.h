/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:22:43 by mstracke          #+#    #+#             */
/*   Updated: 2024/03/06 12:35:04 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to avoid duplications
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

/*We must be able to compile this project with 
and without the -D BUFFER_SIZE flag in addition 
to the usual flags. You can choose the default value of your choice.*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
//# if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1
//#  undef BUFFER_SIZE
//#  define BUFFER_SIZE 42
//# endif

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//to use open & read
# include <fcntl.h>
//need to integrate the libft because of duplicates of ft_calloc
#include "libft.h"

//delete before uploading the project
//# include "../libft/libft.h"
//# include "../ft_printf_recursive/ft_printf.h"

//get_next_line functions
//ft_calloc commented out because of libft-duplicate
char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
//void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
