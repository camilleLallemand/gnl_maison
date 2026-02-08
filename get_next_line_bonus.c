/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/15 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*new_line(char *buff, char *line)
{
	size_t	i;

	if (!buff)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*new_buff(char *buff, char *next, int i)
{
	size_t	j;

	j = 0;
	if (buff[i] == '\0')
	{
		free(buff);
		free(next);
		return (NULL);
	}
	while (buff[i + j])
	{
		next[j] = buff[i + j];
		j++;
	}
	next[j] = '\0';
	free(buff);
	return (next);
}

static char	*creat_buff(char *stock, int fd)
{
	char	*buffer;
	int		statut;

	if (!stock)
	{
		stock = ft_strdup("");
		if (!stock)
			return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(stock), NULL);
	statut = 1;
	while (statut > 0 && !find_nl(stock))
	{
		statut = read(fd, buffer, BUFFER_SIZE);
		if (statut < 0)
			return (free(buffer), free(stock), NULL);
		buffer[statut] = '\0';
		stock = new_res(buffer, stock);
		if (!stock)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stock);
}

static char	*updated_buff(char *s, char **static_buff)
{
	char	*line;
	char	*buff;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	i += (s[i] == '\n');
	j = 0;
	while (s[i + j])
		j++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (free(s), *static_buff = NULL, NULL);
	buff = malloc(sizeof(char) * (j + 1));
	if (!buff)
		return (free(line), free(s), *static_buff = NULL, NULL);
	line = new_line(s, line);
	buff = new_buff(s, buff, (int)i);
	*static_buff = buff;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = creat_buff(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	if (buffer[fd][0] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (updated_buff(buffer[fd], &buffer[fd]));
}
