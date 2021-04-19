/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfranco- <nfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 20:43:11 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/19 21:35:40 by nfranco-         ###   ########.fr       */
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
	strct->rgb_ceiling = create_rgb(0, strct->r_ceiling, strct->g_ceiling, strct->b_ceiling);
	strct->rgb_floor = create_rgb(0, strct->r_floor, strct->g_floor, strct->b_floor);
}
