/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:38:42 by mstracke          #+#    #+#             */
/*   Updated: 2024/03/06 12:34:54 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*DESCRIPTION: 
 Write a function that returns a line read from a
 file descriptor */
/*RETURN VALUE:
 Read line: correct behavior
 NULL: there is nothing else to read, or an error
 occurred */
/* for testing purpose: valgrind --leak-check=full 
--show-leak-kinds=all --track-origins=yes */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

static char	*gnl_lbuf(char *line)
{
	char	*new_lbuf;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
	{
		new_lbuf = ft_substr(line, (i + 1), (ft_strlen(line) - i));
		if (!new_lbuf || *new_lbuf == 0)
		{
			free(new_lbuf);
			new_lbuf = NULL;
		}
		i++;
		while (line[i])
			line[i] = 0;
	}
	else
		new_lbuf = NULL;
	return (new_lbuf);
}

static char	*gnl_read(int fd, char *lbuf, char *rbuf)
{
	char	*oldlinebuf;
	int		len_rbuf;

	len_rbuf = read(fd, rbuf, BUFFER_SIZE);
	if (len_rbuf < 0 || !rbuf)
		return (NULL);
	else if (len_rbuf == 0)
		return (lbuf);
	rbuf[len_rbuf] = 0;
	if (!lbuf)
		oldlinebuf = ft_calloc(1, sizeof(char));
	else
		oldlinebuf = lbuf;
	if (!oldlinebuf)
		return (NULL);
	lbuf = ft_strjoin(oldlinebuf, rbuf);
	free(oldlinebuf);
	oldlinebuf = NULL;
	if (!lbuf)
		return (NULL);
	if (ft_strchr(lbuf, '\n') == 0)
		lbuf = gnl_read(fd, lbuf, rbuf);
	return (lbuf);
}

char	*get_next_line(int fd)
{
	static char	*lbuf[4097];
	char		*line;
	char		*rbuf;

	rbuf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || !rbuf)
	{
		free(rbuf);
		free(lbuf[fd]);
		lbuf[fd] = NULL;
		return (NULL);
	}
	line = gnl_read(fd, lbuf[fd], rbuf);
	free(rbuf);
	rbuf = NULL;
	if (!line)
	{
		free(lbuf[fd]);
		lbuf[fd] = NULL;
		return (NULL);
	}
	lbuf[fd] = gnl_lbuf(line);
	return (line);
}
/*
int	main(void)
{
	int	fd1;
	int	fd2;
	char	path1[] = "test.txt";
	char	path2[] = "test1.txt";
	char	*result;
	int	i;
	int	b;
//	int	fd_result;

	//to write in file
//	fd_result = open("twrite.txt", O_RDWR | O_CREAT);
	//to read from terminal
//	fd2 = 0;
	//to read from file
//	printf("testX");
	fd1 = open(path1, O_RDONLY | O_CREAT);
	if (fd1 == -1)
	{
		perror("Error opening file.\n");
		return (1);
	}
	fd2 = open(path2, O_RDONLY | O_CREAT);
	if (fd2 == -1)
	{
		perror("Error opening file 2.\n");
		return (1);
	}	
	i = 1;
	b = 1;
	while(i < 17)
//	while ((result = get_next_line(fd)) != NULL)
	{
		result = get_next_line(fd1);
		printf("Line %i.0: %s$\n\n", i, result);
		//printf("Length: %zu\n\n", ft_strlen(result));
		free(result);
		result = NULL;
			while ((result = get_next_line(fd2)) != NULL)
			{
				printf("Line %i.%i: %s$\n\n", i, b, result);
			//printf("Length: %zu\n\n", ft_strlen(result));
			free(result);
			result = NULL;
			b++;
//			if (b == 3)
//				close(fd2);
			}
		i++;
	}
	//ft_printf("Line: %s\n", result);
	//ft_putstr_fd(result, fd_result);
//	ft_printf("Length: %d\n", ft_strlen(result));
	close(fd1);
	close(fd2);
	return (0);
}
*/
