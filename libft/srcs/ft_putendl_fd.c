/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:16:19 by mstracke          #+#    #+#             */
/*   Updated: 2023/11/23 10:32:15 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the string ’s’ to the given file descriptor followed by a newline.
*/
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd(10, fd);
}
/*
#include <fcntl.h>

int	main(void)
{
	char	*s = "Hello 42 evaluator";
	int	fd;
//	Open a file descriptor for the "test.txt" file, in
//	truncated write only mode, and create the file if it doesn't
//	already exist. Read and write permissions for the owner, read
//	permissions for the group.
	fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0640);
//	Stop everything if the file could not be opened
	if (fd == -1)
		return (1);
//	Print the fd of the new file
	printf("fd = %d\n", fd);
//	Write into the file descriptor
	ft_putendl_fd(s, fd);
//	Close the file
	close(fd);
	return (0);
}
*/
