/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filled_circle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:59:20 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/08 12:56:59 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    ft_filled_circle(t_vars *strct, int x, int y, int radius, int color)
{
    int x_temp;
    int y_temp;
    int angle;
    int step;
    
    angle = 0;
    x_temp = x;
    y_temp = y;
    step = 1;
    while (angle < 360)
    {
        x_temp = x + (cos(angle) * radius);
        y_temp = y + (sin(angle) * radius);
        //ft_mlx_pixel_put(strct, x_temp, y_temp, color);
        //ft_line(strct, x, y, x_temp, y_temp, color);
        
        angle += step;
    }
}
