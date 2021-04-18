/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:11:01 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/12 19:09:36 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int         ft_render_map(t_vars *strct){
    int     i;
    int     j;
    int     tile_x_position;
    int     tile_y_position;
    int     tile_color;

    i = 0;
    j = 0;
    while (i < strct->map_height)
    {
        while (j < strct->map_width)
        {
            tile_x_position = j * strct->tile_X;
            tile_y_position = i * strct->tile_Y;
            if (strct->map[i][j] == '1' || strct->map[i][j] == 'X')
                tile_color = 0x00000000;
            else if (strct->map[i][j] == '2')
                tile_color = 0xFF0000;
            else
                tile_color = 0xFFFFFF;
            ft_square(strct, (tile_x_position * strct->minimap_scale),
                (tile_y_position * strct->minimap_scale),
                (strct->tile_Y * strct->minimap_scale),
                (strct->tile_X * strct->minimap_scale), tile_color);
            j++;
        }
        j = 0;
        i++;
    }
    return (0);
}

int         ft_render_player(t_vars *strct)
{
    int     color;

    color = 0x0000FF;
    ft_square(strct, (strct->player.x * strct->minimap_scale),
            (strct->player.y * strct->minimap_scale),
            (strct->player.width * strct->minimap_scale),
            (strct->player.height * strct->minimap_scale), color);
    return (0);
}

void        ft_render_2d_rays(t_vars *strct)
{
    ft_draw_line(strct, ((strct->player.x + (strct->player.width / 2)) * strct->minimap_scale),
        ((strct->player.y + (strct->player.height / 2)) * strct->minimap_scale),
        (strct->rays.wall_hit_x * strct->minimap_scale),
        (strct->rays.wall_hit_y * strct->minimap_scale));
}