/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:04:36 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/25 22:39:30 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 40

char				*do_one(char **line, char *s, char **ptr, int i)
{
	*line = ft_substr_gnl(s, 0, i);
	s = ft_substr_gnl(s, i + 1, ft_strlen_gnl(s));
	free(*ptr);
	return (s);
}
// cheguei no final do arquivo
int					do_two(char **line, char *s, char **ptr)
{
	*line = ft_substr_gnl(s, 0, ft_strlen_gnl(s));
    free(*ptr);
    *ptr = NULL;
    s = NULL;
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*str;
	char			*buff;
	char			*temp;
	int				i;

	if (BUFFER_SIZE <= 0 || !line || (read(fd, NULL, 0) < 0) || fd < 0)
		return (-1);
	if (!str){
        str = ft_calloc(1);
        if (!str)
            return (-1);
    }
	if(!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	buff[BUFFER_SIZE] = '\0';
	while (find_char(str, '\n') < 0 && (i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
		temp = str;
		str = ft_strjoin(str, buff);
		free(temp);
	}
	free(buff);
	i = find_char(str, '\n');
	if (i >= 0 && (str = do_one(line, str, &str, i)))
		return (1);
	else
		return (do_two(line, str, &str));
}
