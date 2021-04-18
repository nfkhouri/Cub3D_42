/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:43:11 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/08 12:53:24 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double      ft_normalize_angle(double angle){
    double  remainder;

    if (angle > TWO_PI || angle < 0){
        remainder = fmod(angle, TWO_PI);
        angle = (angle < 0) ? (TWO_PI + remainder) : remainder;
    }
    return (angle);    
}

double      ft_distance_between_points(double x1, double y1, double x2, double y2)
{
    double  distance;

    distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return (distance);    
}

int		create_rgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void		rgb_maker(t_vars *strct)
{
	strct->RGB_ceiling = create_rgb(0, strct->R_ceiling, strct->G_ceiling, strct->B_ceiling);
	strct->RGB_floor = create_rgb(0, strct->R_floor, strct->G_floor, strct->B_floor);
}
