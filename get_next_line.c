/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:40:51 by elise             #+#    #+#             */
/*   Updated: 2025/09/16 15:17:59 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_newline(int fd, char *keep)
{
	int		c;
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;

	c = 1;
	while (c > 0 && (keep == NULL || !(ft_strchr(keep, '\n'))))
	{
		c = read(fd, buffer, BUFFER_SIZE);
		if (c == -1)
		{
			free(keep);
			keep = NULL;
			return (NULL);
		}
		buffer[c] = '\0';
		tmp = keep;
		keep = ft_strjoin(keep, buffer);
		free(tmp);
		if (keep == NULL)
			return (NULL);
	}
	return (keep);
}

char	*extract_line(char **keep)
{
	char	*newline;
	char	*line;
	char	*tmp;
	int		pos;

	newline = ft_strchr(*keep, '\n');
	if (newline)
	{
		pos = newline - *keep;
		line = ft_substr(*keep, 0, pos + 1);
		tmp = *keep;
		*keep = ft_substr(*keep, pos + 1, ft_strlen(*keep) - pos - 1);
		free(tmp);
	}
	else
	{
		line = ft_strdup(*keep);
		free(*keep);
		*keep = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*keep;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep = read_until_newline(fd, keep);
	if (keep == NULL)
		return (NULL);
	if (*keep == '\0')
	{
		free(keep);
		keep = NULL;
		return (NULL);
	}
	line = extract_line(&keep);
	return (line);
}
