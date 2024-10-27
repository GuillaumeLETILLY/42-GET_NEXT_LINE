/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 01:20:37 by gletilly          #+#    #+#             */
/*   Updated: 2024/10/26 01:07:24 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *save)
{
	char	*buffer;
	char	*temp;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(save);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = ft_strjoin(save, buffer);
		free(save);
		save = temp;
	}
	free(buffer);
	return (save);
}

static char	*get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save || !save[0])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = ft_substr(save, 0, i);
	return (line);
}

static char	*save_rest(char *save)
{
	int		i;
	char	*rest;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	rest = ft_substr(save, i, ft_strlen(save) - i);
	free(save);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	line = get_line(save);
	save = save_rest(save);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("olive.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
} */
