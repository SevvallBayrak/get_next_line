/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbayrak <sbayrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:08:35 by sbayrak           #+#    #+#             */
/*   Updated: 2024/12/17 14:47:33 by sbayrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*f_name(int fd, char *buf, char *backup)
{
	int		read_line;

	read_line = 1;
	while (read_line != 0)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		backup = ft_strjoin(backup, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*f_ext(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (NULL);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	line[count + 1] = '\0';
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = f_name(fd, buf, backup);
	free(buf);
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = f_ext(line);
	return (line);
}
