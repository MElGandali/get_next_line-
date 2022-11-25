/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:33:19 by mel-gand          #+#    #+#             */
/*   Updated: 2022/11/06 15:33:22 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_save(char *reserve)
{
	int		i;
	int		j;
	char	*newres;

	i = 0;
	j = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (!reserve[i])
	{
		free(reserve);
		return (NULL);
	}
	newres = malloc(ft_strlen(reserve) - i + 1);
	if (!newres)
		return (NULL);
	i++;
	while (reserve[i])
		newres[j++] = reserve[i++];
	newres[j] = 0;
	free(reserve);
	return (newres);
}

char	*ft_split(char *reserve)
{
	char	*newline;
	int		i;

	i = 0;
	if (!reserve[i])
		return (NULL);
	while (reserve[i] && reserve[i] != '\n')
		i++;
	newline = malloc(i + 2);
	if (!newline)
		return (NULL);
	i = 0;
	while (reserve[i] && reserve[i] != '\n')
	{
		newline[i] = reserve[i];
		i++;
	}
	if (reserve[i] && reserve[i] == '\n')
		newline[i++] = '\n';
	newline[i] = 0;
	return (newline);
}

char	*ft_read(int fd, char *reserve, int nb, char *buff)
{
	nb = 1;
	if (!reserve)
		reserve = ft_strdup("");
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (nb != 0)
	{
		nb = read(fd, buff, BUFFER_SIZE);
		if (nb == -1)
		{
			free(reserve);
			free(buff);
			return (0);
		}
		buff[nb] = 0;
		reserve = ft_strjoin(reserve, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve[OPEN_MAX];
	char		*line;
	char		*buffer;
	int			nb;

	nb = 0;
	buffer = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || fd >= OPEN_MAX)
		return (NULL);
	reserve[fd] = ft_read(fd, reserve[fd], nb, buffer);
	if (!reserve[fd])
		return (NULL);
	line = ft_split(reserve[fd]);
	reserve[fd] = ft_save(reserve[fd]);
	return (line);
}
