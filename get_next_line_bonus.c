/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarhat <ofarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:03:38 by ofarhat           #+#    #+#             */
/*   Updated: 2022/11/27 01:24:37 by ofarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
                                
char	*ft_read(int fd, char *save)
{
	char	*str;
	int		check;

	if (!save)
		save = ft_strdup("");
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (0);
	check = 1;
	while (!ft_strchr(save, '\n') && check)
	{
		check = read(fd, str, BUFFER_SIZE);
		if (check == -1)
		{
			free(str);
			free(save);
			return (0);
		}
		str[check] = '\0';
		save = ft_strjoin(save, str);
	}
	free(str);
	return (save);
}

char	*ft_line(char *save)
{
	char	*firstl;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(save);
	firstl = malloc(len + 2);
	if (!firstl)
		return (0);
	while (save[i] && (save[i] != '\n'))
	{
		firstl[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		firstl[i] = save[i];
		i++;
	}
	firstl[i] = '\0';
	return (firstl);
}

char	*ft_nline(char *save)
{
	char	*nextl;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	nextl = malloc(ft_strlen(save) - i + 1);
	if (!nextl)
		return (0);
	while (save[i])
	{
		nextl[j] = save[i + 1];
		j++;
		i++;
	}
	nextl[j] = '\0';
	free(save);
	return (nextl);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd] || !*save[fd])
	{
		free (save[fd]);
		save[fd] = NULL;
		return (save[fd]);
	}
	line = ft_line(save[fd]);
	save[fd] = ft_nline(save[fd]);
	return (line);
}
