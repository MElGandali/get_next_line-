/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:14:57 by mel-gand          #+#    #+#             */
/*   Updated: 2022/10/28 20:16:04 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	newres = malloc((ft_strlen(reserve) - i + 1) * sizeof(char));
	if (!newres)
		return (NULL);
	i++;
	while (reserve[i])
		newres[j++] = reserve[i++];
	newres[j] = 0;
	free(reserve);
	return (newres);
}

char	*ft_split(char *s)
{
	char	*newstring;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	newstring = malloc(i + 2);
	if (!newstring)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		newstring[i] = s[i];
		i++;
	}
	if (s[i] && s[i] == '\n')
		newstring[i++] = '\n';
	newstring[i] = 0;
	return (newstring);
}

char	*ft_read(int fd, char *reserve, int nb, char *buff)
{
	if (!reserve)
		reserve = ft_strdup("");
	nb = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	while (nb != 0)
	{
		nb = read(fd, buff, BUFFER_SIZE);
		if (nb == -1)
		{
			free(buff);
			free(reserve);
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
	static char	*reserve;
	char		*line;
	char		*buffer;
	int			nb;

	nb = 0;
	buffer = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	reserve = ft_read(fd, reserve, nb, buffer);
	if (!reserve)
		return (NULL);
	line = ft_split(reserve);
	reserve = ft_save(reserve);
	return (line);
}
