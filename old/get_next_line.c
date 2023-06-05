/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksansom <ksansom@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:02:14 by ksansom           #+#    #+#             */
/*   Updated: 2023/06/05 14:42:21 by ksansom          ###   ########.fr       */
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
		return (NULL);
	}
	leftover = ft_calloc(((ft_strlen(str) - i) + 1), 1);
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
	if (read(fd, str, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
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
	static char	*string;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 \
		|| BUFFER_SIZE > INT_MAX - 1)
		return (NULL);
	string = ft_read_chunks(fd, string);
	if (!string)
		return (NULL);
	line = ft_line(string);
	string = ft_next(string);
	if (!string || string[0] == '\0')
	{
		free(string);
		string = NULL;
	}
	return (line);
}
