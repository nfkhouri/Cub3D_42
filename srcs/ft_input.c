/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfranco- <nfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:26:21 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/19 21:35:48 by nfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int		ft_check_input(t_vars *strct)
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	fd = open(strct->map_path, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_eval_line(line, strct) == -1)
		{
			ft_close_free_gnl(fd, line);
			return (-1);
		}
		free(line);
	}
	if (ft_eval_line(line, strct) == -1)
	{
		ft_close_free_gnl(fd, line);
		return (-1);
	}
	ft_close_free_gnl(fd, line);
	strct->tile_x = strct->window_width / strct->map_width;
	strct->tile_y = strct->window_height / strct->map_height;
	rgb_maker(strct);
	return (0);
}

void	ft_count_sprites(t_vars *strct, char *line)
{
	int		i;
	int		len;

	i = 0;
	len = (ft_strlen(line));
	while (i < len)
	{
		if (line[i] == '2')
			strct->num_of_sprites++;
		i++;
	}
}

void	ft_eval_aux1(t_vars *strct, char *line)
{
	if (ft_strlen(line) > strct->map_width)
		strct->map_width = ft_strlen(line);
	strct->map_height++;
	ft_count_sprites(strct, line);
}

int		ft_1(t_vars *strct, char *line, int i)
{
	if ((line[i] == 'R') && line[i + 1] == ' ')
	{
		strct->check = 1;
		if (ft_resolution(line, strct) == -1)
			return (-1);
	}
	return (1);
}

int		ft_2(t_vars *strct, char *line, int i)
{
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
	{
		strct->check = 1;
		if (ft_colors(line, strct) == -1)
			return (-1);
	}
	return (1);
}

int		ft_3(t_vars *strct, char *line, int i)
{
	if (((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O'
		&& line[i + 2] == ' ') || (line[i] == 'W' && line[i + 1] == 'E' &&
		line[i + 2] == ' ') || (line[i] == 'E' && line[i + 1] == 'A' &&
		line[i + 2] == ' ') || (line[i] == 'S' && line[i + 1] == ' '))
	{
		strct->check = 1;
		if (ft_textures(line, strct) == -1)
			return (-1);
	}
	return (1);
}

int		ft_4(t_vars *strct, char *line, int i)
{
	if (line[i] >= 8 && line[i] <= 13 || ft_strncmp(line, "\000", 5) == 0)
	{
		strct->check = 1;
		return (1);
	}
	return (1);
}

int		ft_5(t_vars *strct, char *line, int i)
{
	if (line[i] == ' ' || line[i] == '1')
	{
		strct->check = 1;
		if (ft_strchr(line, '1') != 0)
		{
			ft_eval_aux1(strct, line);
			return (0);
		}
	}
	return (1);
}

int		ft_eval_line(char *line, t_vars *strct)
{
	int		i;
	int		res;

	i = 0;
	res = ft_1(strct, line, i);
	if (strct->check != 0)
		res = ft_2(strct, line, i);
	if (strct->check != 0)
		res = ft_3(strct, line, i);
	if (strct->check != 0)
		res = ft_4(strct, line, i);
	if (strct->check != 0)
		res = ft_5(strct, line, i);
	else
	{
		ft_putendl_fd("Map is not valid", 1);
		return (-1);
	}
	if (res == -1)
		return (-1);
	return (1);
}
