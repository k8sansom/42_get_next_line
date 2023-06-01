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
		return (0);
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
		return (0);
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
	char	*buffer_read;
	int		bytes_read;

	if (!str)
		str = ft_calloc(1, 1);
	buffer_read = ft_calloc(BUFFER_SIZE + 1, 1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer_read, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer_read);
			return (0);
		}
		buffer_read[bytes_read] = '\0';
		str = ft_join_clean(str, buffer_read);
		if (ft_strchr(buffer_read, '\n'))
			break ;
	}
	free(buffer_read);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*string;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	string = ft_read_chunks(fd, string);
	if (!string)
		return (0);
	line = ft_line(string);
	string = ft_next(string);
	return (line);
}
