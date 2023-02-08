/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleon <sleon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:55:22 by sleon             #+#    #+#             */
/*   Updated: 2022/12/02 12:34:17 by sleon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *line)
{
	char	*buff;
	int		byte_readed;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	byte_readed = 1;
	while (!ft_strchr(line, '\n') && byte_readed != 0)
	{
		byte_readed = read(fd, buff, BUFFER_SIZE);
		if (byte_readed == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte_readed] = '\0';
		line = ft_strjoingnl(line, buff);
	}
	free (buff);
	return (line);
}

char	*get_next_line(int fd, int reset)
{
	char		*buff;
	static char	*line = NULL;

	if (reset)
		return (free(line), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_read_line(fd, line);
	if (!line)
		return (NULL);
	buff = ft_line_to_buff(line);
	line = ft_read_new_line(line);
	return (buff);
}
