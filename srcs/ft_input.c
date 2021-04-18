/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:26:21 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/17 16:10:37 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int         ft_check_input(t_vars *strct)
{
    int     fd;
    char    *line;
    int     i;
    
    line = NULL;
    fd = open(strct->map_path, O_RDONLY);
    while(get_next_line(fd, &line) == 1)
    {
        if (ft_eval_line(line, strct) == -1)
        {
            close(fd);
            free(line);
            return (-1);
        }
        free(line);
    }
    if (ft_eval_line(line, strct) == -1)
    {
        close(fd);
        free(line);
        return (-1);
    }
    close(fd);
    free(line);
    strct->tile_X = strct->window_width / strct->map_width;
    strct->tile_Y = strct->window_height / strct->map_height;
	rgb_maker(strct);
    return (0);
}

void		ft_count_sprites(t_vars *strct, char *line)
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

int         ft_eval_line(char *line, t_vars *strct)
{
    int     i;
	
    i = 0;
    if ((line[i] == 'R') && line[i + 1] == ' ')
    {
        if (ft_resolution(line, strct) == -1)
            return (-1);
    }
    else if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
    {
        if (ft_colors(line, strct) == -1)
            return (-1);
    }
    else if (((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O' && line[i + 2] == ' ')
        || (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ') 
        || (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
        || (line[i] == 'S' && line[i + 1] == ' '))
    {
        if (ft_textures(line, strct) == -1)
            return (-1);
    }
    else if (line[i] >= 8 && line[i] <= 13)
        return (1);
    else if (ft_strncmp(line, "\000", 5) == 0)
        return (1);
    else if(line[i] == ' ' || line[i] == '1')
    {
        if (ft_strchr(line, '1') != 0)
        {
            if (ft_strlen(line) > strct->map_width)
                strct->map_width = ft_strlen(line);
            strct->map_height++;
			ft_count_sprites(strct, line);
            return (0);
         }
        else
            return (1);
    }
    else
    {
        ft_putendl_fd("Map is not valid", 1); //Corrigir isso, pois ele tem que checar o mapa por último tb
        return (-1);
    }
    return (1);
}