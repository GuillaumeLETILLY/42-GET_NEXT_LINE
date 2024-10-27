/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 01:20:37 by gletilly          #+#    #+#             */
/*   Updated: 2024/10/26 00:42:19 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*save[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	save[fd] = read_file(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = get_line(save[fd]);
	save[fd] = save_rest(save[fd]);
	return (line);
}

/* #include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	char	*line;

	fd1 = open("olive.txt", O_RDONLY);
	fd2 = open("tomate.txt", O_RDONLY);
	fd3 = open("patate.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		printf("Erreur lors de l'ouverture d'un fichier\n");
		return (1);
	}
	while ((line = get_next_line(fd1)) || (line = get_next_line(fd2)) 
		|| (line = get_next_line(fd3)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
} */
