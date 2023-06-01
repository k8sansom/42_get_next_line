/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksansom <ksansom@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:02:14 by ksansom           #+#    #+#             */
/*   Updated: 2023/06/01 14:44:09 by ksansom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join_clean(char *temp, char *buf)
{
	char	*join;

	join = ft_strjoin(temp, buf);
	free(temp);
	return (join);
}

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*update;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (0);
	}
	update = ft_calloc((ft_strlen(buffer) - i + 1), 1);
	i++;
	j = 0;
	while (buffer[i])
		update[j++] = buffer[i++];
	free(buffer);
	return (update);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_read_chunks(int fd, char *res)
{
	char	*b_size_read;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	b_size_read = ft_calloc(BUFFER_SIZE + 1, 1);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, b_size_read, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(b_size_read);
			return (0);
		}
		b_size_read[byte_read] = '\0';
		res = ft_join_clean(res, b_size_read);
		if (ft_strchr(b_size_read, '\n'))
			break ;
	}
	free(b_size_read);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	buffer = ft_read_chunks(fd, buffer);
	if (!buffer)
		return (0);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
