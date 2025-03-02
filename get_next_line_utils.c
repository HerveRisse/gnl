/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:39:25 by hrisse            #+#    #+#             */
/*   Updated: 2025/02/27 10:40:08 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *extract_line(char **stash)
{
	char *line;
	char *newline_pos;
	char *temp;
	size_t line_len;

	if (!*stash || !**stash)
		return (NULL);
	newline_pos = ft_strchr(*stash, '\n');
	if (newline_pos)
	{
		line_len = newline_pos - *stash + 1;
		line = ft_substr(*stash, 0, line_len);
		if (!line)
			return (NULL);
		temp = ft_strdup(newline_pos + 1);
		if (!temp)
		{
			free(line);
			return (NULL);
		}
		free(*stash);
		*stash = temp;
		return (line);
	}
	line = ft_strdup(*stash);
	if (!line)
		return (NULL);
	free(*stash);
	*stash = NULL;
	return (line);
}

static char *read_and_stash(int fd, char **stash)
{
	char *buffer;
	char *temp;
	ssize_t bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*stash, buffer);
		if (!temp)
		{
			free(buffer);
			return (NULL);
		}
		free(*stash);
		*stash = temp;
	}
	free(buffer);
	return (*stash);
}

char *get_next_line(int fd)
{
	static char *stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!read_and_stash(fd, &stash))
		return (NULL);
	return (extract_line(&stash));
}
