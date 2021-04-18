/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:13:39 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/17 22:00:16 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double			ft_calc_angle(t_vars *strct, int i)
{
	double	angle;
	double	j;

	// if(strct->player.rotation_angle >= 0 && strct->player.rotation_angle <= PI)
	// {
	// 	strct->sprite[i].x = strct->sprite[i].x + strct->tile_X;
	// 	strct->sprite[i].y = strct->sprite[i].y + strct->tile_Y; 
	// }
	// j = atan2(strct->sprite[i].y - (double)strct->player.y,
	// 	strct->sprite[i].x - (double)strct->player.x);
	// if(strct->player.rotation_angle >= 0 && strct->player.rotation_angle <= PI)
	// {
	// 	strct->sprite[i].x = ((strct->sprite[i].x + 1) * strct->tile_X);
	// 	strct->sprite[i].y = ((strct->sprite[i].y + 1) * strct->tile_Y);
	// }
	// else
	// {
	// 	strct->sprite[i].x = (strct->sprite[i].x * strct->tile_X);
	// 	strct->sprite[i].y = (strct->sprite[i].y * strct->tile_Y);
	// }
	angle = atan2(strct->sprite[i].y - strct->player.y,
		strct->sprite[i].x - strct->player.x) - strct->player.rotation_angle;
	// angle = strct->player.rotation_angle - j;
	if (angle > PI)
		angle -= TWO_PI;
	if (angle < -PI)
		angle += TWO_PI;
	angle = fabs(angle);
	// ft_normalize_angle(angle);
	return (angle);
}

void			ft_calc_distance(t_vars *strct, double angle_sprite_player, int i)
{
	double		epsilon;

	epsilon = 0.2;
	strct->sprite[i].distance =
			ft_distance_between_points(strct->sprite[i].x, strct->sprite[i].y,
			strct->player.x, strct->player.y);
	if (angle_sprite_player < ((strct->player.fov_angle / 2) + epsilon))
	{
		strct->sprite[i].is_visible = 1;
		strct->sprite[i].angle = angle_sprite_player;
		strct->sprite[i].distance =
			ft_distance_between_points(strct->sprite[i].x, strct->sprite[i].y,
			strct->player.x, strct->player.y);
	}
	else
		strct->sprite[i].is_visible = 0;
}

void			ft_sort_sprites(t_vars *strct)
{
	int			i;
	int			j;
	t_sprites	temp;

	i = 0;
	while (i < strct->num_of_sprites)
	{
		j = i + 1;
		while (j < strct->num_of_sprites)
		{
			if (strct->sprite[i].distance < strct->sprite[j].distance)
			{
				temp = strct->sprite[i];
				strct->sprite[i] = strct->sprite[j];
				strct->sprite[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void			ft_render_single_sprite(t_vars *strct, int i)
{
	double	distance_proj_plane;
	double	screen_pos_x;
	int		x;
	double	angle;
	double	perp_distance;

	distance_proj_plane = (strct->window_width / 2)
        / tan(strct->player.fov_angle / 2);
	perp_distance = strct->sprite[i].distance * cos(strct->sprite[i].angle);
	strct->sprite[i].height = (strct->tile_Y / perp_distance) * distance_proj_plane;
	strct->sprite[i].width = (strct->tile_X / strct->sprite[i].distance) * distance_proj_plane;

	strct->sprite[i].top_y = (strct->window_height / 2) - (strct->sprite[i].height / 2);
	strct->sprite[i].top_y = (strct->sprite[i].top_y < 0) ? 0 : strct->sprite[i].top_y;
	
	strct->sprite[i].bottom_y = (strct->window_height / 2) + (strct->sprite[i].height / 2);
	strct->sprite[i].bottom_y = (strct->sprite[i].bottom_y > strct->window_height) ? strct->window_height : strct->sprite[i].bottom_y;

	angle = atan2(strct->sprite[i].y - strct->player.y,
		strct->sprite[i].x - strct->player.x);
	angle = atan2(strct->sprite[i].y - strct->player.y,
		strct->sprite[i].x - strct->player.x) - strct->player.rotation_angle;
	screen_pos_x = tan(angle) * distance_proj_plane;
	strct->sprite[i].left_x = (strct->window_width / 2) + screen_pos_x;
	strct->sprite[i].right_x = strct->sprite[i].left_x + strct->sprite[i].width;

	x = strct->sprite[i].left_x;
	while (x < strct->sprite[i].right_x)
	{
		x++;
		ft_draw_sprite(strct, x - 1, i);
	}
}

void			ft_render_sprites(t_vars *strct)
{
	int			i;
	double		angle_sprite_player;
	
	i = 0;
	printf("rotation angle: %f\n", strct->player.rotation_angle);
	while (i < strct->num_of_sprites)
	{
		angle_sprite_player = ft_calc_angle(strct, i);
		ft_calc_distance(strct, angle_sprite_player, i);
		i++;
	}
	i = 0 ;
	ft_sort_sprites(strct);
	while (i < strct->num_of_sprites)
	{
		if (strct->sprite[i].is_visible == 1)
		{
			ft_render_single_sprite(strct, i);
		}
		i++;
	}
}