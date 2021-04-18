/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:50:18 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/03 22:47:06 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void        ft_mlx_pixel_put(t_vars *strct, int x, int y, int color)
{
    char    *dst;

    dst = strct->addr + (y * strct->line_length + x * ((strct->bits_per_pixel )/ 8));
    *(unsigned int*)dst = color;
}
