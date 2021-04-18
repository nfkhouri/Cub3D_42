/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:24:30 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/15 11:50:30 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    ft_line(t_vars *strct, int x1, int y1, int x2, int y2, int color)
{
    int smallest;
    int y_step;
    int x_step;
    int i;
    
    i = 0;
    if ((x2 - x1) <= (y2 - y1)){
        smallest = (x2 - x1);
        y_step = ((y2 - y1) / (x2 - x1));
        x_step = 1;
    }
    else {
        smallest = (y2 - y1);
        x_step = ((x2 - x1) / (y2 - y1));
        y_step = 1;
    }
    while (i <=  smallest)
    {
        ft_mlx_pixel_put(strct, x1, y1, color);
        y1 += y_step;
        x1 += x_step;
        i++;
    }
}
