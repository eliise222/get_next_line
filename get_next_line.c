/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elise <elise@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:40:51 by elise             #+#    #+#             */
/*   Updated: 2025/09/22 14:07:15 by elise            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	read_to_buffer(int fd, char *buf, size_t bufsize)
{
	ssize_t	c;

	c = read(fd, buf, bufsize);
	if (c > 0)
		buf[c] = '\0';
	return (c);
}

static char	*read_loop(int fd, char *keep, size_t *len)
{
	char	*buf;
	char	*tmp;
	ssize_t	c;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!keep || !ft_strchr(keep, '\n'))
	{
		c = read_to_buffer(fd, buf, BUFFER_SIZE);
		if (c <= 0)
			break ;
		tmp = keep;
		keep = ft_strjoin(keep, buf);
		free(tmp);
		*len += c;
		if (!keep || *len > MAX_LINE_LENGTH)
			break ;
	}
	free(buf);
	if (c == -1 || *len > MAX_LINE_LENGTH)
		return (free(keep), NULL);
	return (keep);
}

char	*read_until_newline(int fd, char *keep)
{
	size_t	len;

	len = 0;
	if (keep)
		len = ft_strlen(keep);
	return (read_loop(fd, keep, &len));
}

char	*extract_line(char **keep)
{
	char	*newline;
	char	*line;
	char	*tmp;
	size_t	pos;

	if (keep == NULL || *keep == NULL || **keep == '\0')
		return (NULL);
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
	if (keep == NULL || *keep == '\0')
	{
		free(keep);
		keep = NULL;
		return (NULL);
	}
	line = extract_line(&keep);
	return (line);
}
