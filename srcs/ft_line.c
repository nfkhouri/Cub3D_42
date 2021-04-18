/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:24:30 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/12 19:43:33 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    ft_large_slope(t_vars *strct, int slope_sign, int x1, int y1, int x2, int y2)
{
    int P;
    int dx;
    int dy;

    dx = x2 - x1;
    dy = abs(y2 - y1);
    P = (2 * dx) - dy;
    if (y1 < y2){
        while(y1 <= y2)
        {
            ft_mlx_pixel_put(strct, x1, y1, strct->color);
            y1++;
            if(P < 0)
                P += 2 * dx;
            else{
                P += (2 * dx) - (2 * dy);
                x1++; 
            }
        }
    }
    else
    {
        while(y2 <= y1)
        {
            ft_mlx_pixel_put(strct, x1, y1, strct->color);
            y1--;
            if(P < 0)
                P += 2 * dx;
            else{
                P += (2 * dx) - (2 * dy);
                x1++; 
            }
        }
    }
}

void    ft_small_slope(t_vars *strct, int slope_sign, int x1, int y1, int x2, int y2)
{
    int P;
    int dx;
    int dy;

    dx = x2 - x1;
    dy = abs(y2 - y1);
    P = (2 * dy) - dx;
    while(x1 <= x2)
    {
        ft_mlx_pixel_put(strct, x1, y1, strct->color);
        x1++;
        if(P < 0)
            P += 2 * dy;
        else{
            P += (2 * dy) - (2 * dx);
            y1 = (slope_sign == -1) ? y1 - 1 : y1 + 1; //se slope for negativo, y decrementa, se for positivo y incrementa
        }
    }
}

int     ft_draw_line(t_vars *strct, int x1, int y1, int x2, int y2)
{
    int x;
    int y;
    int dx;
    int dy;
    int slope; //slope >1 = 1, slope <1 = 0
    int slope_sign; //negative slope = -1, positive slope = 1;

    dx = x2 - x1;
    dy = y2 - y1;
    if (dx == 0)
    {
        if (dy < 0)
        {
            x = x2;
            y = y2;
            x2 = x1;
            y2 = y1;
        }
        else
        {
            x = x1;
            y = y1; 
        }
        while (y < y2){
            ft_mlx_pixel_put(strct, x, y, strct->color);
            y++;
        }
        return (0);
    }
    if (dy == 0)
    {
        if (dx < 0)
        {
            x = x2;
            y = y2;
            x2 = x1;
            y2 = y1;
        }
        else
        {
            x = x1;
            y = y1; 
        }
        while (x < x2){
            ft_mlx_pixel_put(strct, x, y, strct->color);
            x++;
        }
        return (0);
    }
    slope = (abs(dy) > abs(dx)) ? 1 : 0;
    if (dx < 0)
    {
        if (dy > 0)
            slope_sign = -1;
        else
            slope_sign = 1;
        x = x2;
        y = y2;
        x2 = x1;
        y2 = y1;
    }
    else
    {
        if (dy > 0)
            slope_sign = 1;
        else
            slope_sign = -1;
        x = x1;
        y = y1;
    }
    if (slope == 1)
        ft_large_slope(strct, slope_sign, x, y, x2, y2);
    else 
        ft_small_slope(strct, slope_sign, x, y, x2, y2); //função do video
    return (0);
}