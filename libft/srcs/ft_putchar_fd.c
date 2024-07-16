/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:30:04 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/23 10:30:31 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the character ’c’ to the given file descriptor. */
/* Once a file descriptor is opened with an access mode permitting writing, */
/* we will be able to write to the file it references */
/* thanks to the write system call from the <unistd.h> library. */
/* Prototype: */
/* fd = open("path/to/file", O_WRONLY | O_TRUNC | O_CREAT, 0640); */ 
/* (truncated write only mode (overwrite with 0 when exists) | */
/* create the file if it doesn't already exist with read and write */
/* permissions for the owner, */
/* read	permissions for the group) */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
