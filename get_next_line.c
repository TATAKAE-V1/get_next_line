/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarhat <ofarhat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 03:45:43 by ofarhat           #+#    #+#             */
/*   Updated: 2022/11/25 18:49:39 by ofarhat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = ft_read(fd, save);
	if (!save || !*save)
	{
		free (save);
		save = NULL;
		return (save);
	}
	line = ft_line(save);
	save = ft_nline(save);
	return (line);
}
