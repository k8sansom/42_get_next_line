/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksansom <ksansom@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:49:03 by ksansom           #+#    #+#             */
/*   Updated: 2023/06/05 10:36:54 by ksansom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_join_clean(char *str, char *buffer_read)
{
	char	*join;

	join = ft_strjoin(str, buffer_read);
	free(str);
	return (join);
}

char	*ft_next(char *str)
{
	int		i;
	int		j;
	char	*leftover;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	leftover = ft_calloc((ft_strlen(str) - i + 1), 1);
	i++;
	j = 0;
	while (str[i])
		leftover[j++] = str[i++];
	free(str);
	return (leftover);
}

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_read_chunks(int fd, char *str)
{
	char	*buffer;
	int		bytes_read;

	if (!str)
		str = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		str = ft_join_clean(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*string[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 \
		|| BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	string[fd] = ft_read_chunks(fd, string[fd]);
	if (!string[fd])
		return (NULL);
	line = ft_line(string[fd]);
	string[fd] = ft_next(string[fd]);
	return (line);
}
