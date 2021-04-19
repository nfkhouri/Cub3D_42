/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfranco- <nfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:47:10 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/19 21:35:43 by nfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int		ft_get_direction(t_vars *strct)
{
	if (strct->player.direction == 'S')
		strct->player.rotation_angle = PI / 2;
	else if (strct->player.direction == 'W')
		strct->player.rotation_angle = PI;
	else if (strct->player.direction == 'N')
		strct->player.rotation_angle = (3 * PI) / 2;
	else if (strct->player.direction == 'E')
		strct->player.rotation_angle = 0;
	else
	{
		ft_putendl_fd("There is no player position.", 1);
		return (-1);
	}
	return (0);
}

int		ft_map_x(t_vars *strct, int i, int j)
{
	if (i != 0)
		if (!ft_strchr("1X", strct->map[i - 1][j]))
			return (-1);
	if (i != strct->map_height - 1)
		if (!ft_strchr("1X", strct->map[i + 1][j]))
			return (-1);
	if (j != 0)
		if (!ft_strchr("1X", strct->map[i][j - 1]))
			return (-1);
	if (j != strct->map_width - 1)
		if (!ft_strchr("1X", strct->map[i][j + 1]))
			return (-1);
	return (0);
}

int		ft_map_0(t_vars *strct, int i, int j)
{
	if (i == 0 || i == strct->map_height - 1 || j == 0 \
			|| j == strct->map_width - 1)
		return (-1);
	else
	{
		if (!ft_strchr("012NSWE", strct->map[i - 1][j]))
			return (-1);
		if (!ft_strchr("012NSWE", strct->map[i + 1][j]))
			return (-1);
		if (!ft_strchr("012NSWE", strct->map[i][j - 1]))
			return (-1);
		if (!ft_strchr("012NSWE", strct->map[i][j + 1]))
			return (-1);
	}
	return (0);
}

int		ft_map_is_valid(t_vars *strct)
{
	int		i;
	int		j;
	int		res;

	i = -1;
	j = 0;
	while (++i < strct->map_height)
	{
		while (++j < strct->map_width)
		{
			if (strct->map[i][j] == 'X')
			{
				if ((res = ft_map_x(strct, i, j)) == -1)
					return (-1);
			}
			else if (strct->map[i][j] == '0')
			{
				if ((res = ft_map_0(strct, i, j)) == -1)
					return (-1);
			}
		}
		j = 0;
	}
	return (0);
}

int		ft_map_aux1(char *str, int i)
{
	while (str[ft_strlen(str) - i] == ' ')
		i++;
	if (str[ft_strlen(str) - i] != '1')
		return (-1);
	return (1);
}

void	ft_map_aux2(t_vars *strct, int line_nbr, int i)
{
	strct->sprite[strct->sprite_id].x = i * strct->tile_x;
	strct->sprite[strct->sprite_id].y = line_nbr * strct->tile_y;
	strct->sprite_id++;
}

void	ft_map_aux3(t_vars *strct, char *str, int line_nbr, int i)
{
	strct->player.x = ((i * strct->tile_x) + (strct->tile_x / 2));
	strct->player.y = ((line_nbr * strct->tile_y) + (strct->tile_y / 2));
	strct->player.direction = str[i];
}

char	*ft_map_aux4(t_vars *strct, char *temp, char *str, int i)
{
	if (strct->map_width > ft_strlen(str))
	{
		while (i++ < strct->map_width)
			temp[i - 1] = 'X';
	}
	return (temp);
}

int		ft_map_aux5(t_vars *strct, char *temp, char *str, int line_nbr, int i)
{
	if (ft_strchr(" \t\n\v\f\r", str[i]))
		temp[i] = 'X';
	else if (ft_strchr("2", str[i]))
	{
		temp[i] = str[i];
		ft_map_aux2(strct, line_nbr, i);
	}
	else if (ft_strchr("NSWE", str[i]))
	{
		if (strct->player.x != 0 || strct->player.y != 0)
		{
			ft_putendl_fd("Player position is invalid.", 1);
			free(temp);
			return (-1);
		}
		ft_map_aux3(strct, str, line_nbr, i);
		temp[i] = '0';
	}
	else if (ft_strchr("012", str[i]))
		temp[i] = str[i];
	else
		return (-1);
	return (1);
}

int		ft_map(char *str, t_vars *strct, int line_nbr)
{
	int		i;
	char	*temp;
	int		res;

	i = 1;
	res = ft_map_aux1(str, i);
	i = -1;
	temp = ft_calloc((strct->map_width + 1) * sizeof(char));
	while (str[++i] != '\0' && ft_strchr("012NSWE \t\n\v\f\r", str[i]))
	{
		res = ft_map_aux5(strct, temp, str, line_nbr, i);
	}
	strct->map[line_nbr] = ft_map_aux4(strct, temp, str, i);
	if (res == -1)
		return (-1);
	return (1);
}

int		ft_first_if(t_vars *strct, char *line, int line_nbr, int fd)
{
	if (ft_strchr(line, '1') != 0)
	{
		if (ft_map(line, strct, line_nbr) < 0)
		{
			ft_putendl_fd("Map is not valid.", 1);
			free(line);
			close(fd);
			return (-1);
		}
		line_nbr++;
	}
	return (line_nbr);
}

int		ft_map_and_dir(t_vars *strct)
{
	if (ft_map_is_valid(strct) < 0)
	{
		ft_putendl_fd("Map is not valid.", 1);
		return (-1);
	}
	if (ft_get_direction(strct) == -1)
		return (-1);
	return (0);
}

void	ft_close_free_gnl(int fd, char *line)
{
	close(fd);
	free(line);
}

int		ft_last_line(t_vars *strct, char *line, int fd, int line_nbr)
{
	if (ft_strchr(line, '1') != 0 && (ft_map(line, strct, line_nbr) < 0))
	{
		ft_putendl_fd("Map is not valid.", 1);
		ft_close_free_gnl(fd, line);
		return (-1);
	}
	ft_close_free_gnl(fd, line);
	return (ft_map_and_dir(strct));
}

int		ft_check_map(t_vars *strct)
{
	int		fd;
	char	*line;
	int		line_nbr;

	line_nbr = 0;
	line = NULL;
	fd = open(strct->map_path, O_RDONLY);
	strct->map = (char **)ft_calloc((strct->map_height + 1) * sizeof(char *));
	ft_init_sprites(strct);
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strchr("NSWE\t\n\v\f\r", line[0]))
		{
			free(line);
			continue;
		}
		else if (line[0] == ' ' || line[0] == '1')
		{
			line_nbr = ft_first_if(strct, line, line_nbr, fd);
		}
		free(line);
	}
	return (ft_last_line(strct, line, fd, line_nbr));
}
