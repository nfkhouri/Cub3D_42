/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:59:03 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/08 13:45:32 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    ft_black_screen(t_vars *strct)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < strct->window_width) {
        while (j < strct->window_height) {
            ft_mlx_pixel_put(strct, i, j, 0x00000000);
            j++;
        }
        j = 0;
        i++;
    }
}

void    ft_square(t_vars *strct, int x, int y, int height, int width, unsigned int color)
{
    int x_temp;
    int y_temp;

    x_temp = x;
    y_temp = y;
    while (y < (height + y_temp))
    {
        while (x < (width + x_temp))
        {
            ft_mlx_pixel_put(strct, x, y, color);
            x++;
        }
        x = x_temp;
        y++;
    }
}