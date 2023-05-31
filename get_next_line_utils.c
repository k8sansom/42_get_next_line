/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksansom <ksansom@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:03:10 by ksansom           #+#    #+#             */
/*   Updated: 2023/05/31 10:24:09 by ksansom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dest;

	len = ft_strlen(s) + 1;
	i = 0;
	dest = (char *)malloc(sizeof(char) * len);
	if (!dest)
		return (0);
	while (s[i])
	{
		((unsigned char *)dest)[i] = ((unsigned char *)s)[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}