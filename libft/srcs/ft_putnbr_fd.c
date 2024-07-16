/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:41:37 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/23 11:30:52 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* DESCRIPTION: */
/* Outputs the integer ’n’ to the given file */
/* descriptor. write(fd, "-2147483648", 11) */

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar_fd(45, fd);
		ft_putnbr_fd((n * (-1)), fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd(((n % 10) + 48), fd);
	}
	else 
		ft_putchar_fd((n + 48), fd);
}

/*
#include <fcntl.h>

int	main(void)
{
//	char	*s = "Hello 42 evaluator";
	int	n;
	int	fd;
	n = -499918;
//	Open a file descriptor for the "test.txt" file, in
//	truncated write only mode, and create the file if it doesn't
//	already exist. Read and write permissions for the owner, read
//	permissions for the group.
	fd = open("putnbr_fd.txt", O_WRONLY | O_TRUNC | O_CREAT, 0640);
//	fd = 1;
//	Stop everything if the file could not be opened
	if (fd == -1)
		return (1);
//	Print the fd of the new file
	printf("fd = %d\n", fd);
//	Write into the file descriptor
	ft_putnbr_fd(n, fd);
//	Close the file
	close(fd);
	return (0);
}
*/
