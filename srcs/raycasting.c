/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfranco- <nfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:51:29 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/19 21:35:41 by nfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int         ft_which_texture(t_vars *strct, double ray_angle)
{
    int     i;
    if (strct->rays.is_facing_up)
    {
        if (strct->rays.was_hit_vertical == 1)
        {
            i = (strct->rays.is_facing_right) ? 2 : 3;
        }
        else
            i = 0;
    }
    else
    {
        if (strct->rays.was_hit_vertical == 1)
        {
            i = (strct->rays.is_facing_right) ? 2 : 3;
        }
        else
            i = 1;
    }
    return (i);
}

void        ft_render_3d_rays(t_vars *strct, double ray_angle)
{
    double  wall_strip_height;
    double  distance_proj_plane;
    int     wall_top_pixel;
    int     wall_bottom_pixel;
    int     i;
    
    //calculate the distance to the projection plane
    distance_proj_plane = (strct->window_width / 2)
        / tan(strct->player.fov_angle / 2);
    //projected wall height
    wall_strip_height = (strct->tile_y / (strct->rays.distance
        * cos(ray_angle - strct->player.rotation_angle)))
        * distance_proj_plane;
    wall_top_pixel = (strct->window_height / 2) - (wall_strip_height / 2);
    wall_top_pixel = (wall_top_pixel <= 0) ? 1 : wall_top_pixel;
    wall_bottom_pixel = (strct->window_height / 2) + (wall_strip_height / 2);
    wall_bottom_pixel = (wall_bottom_pixel >= strct->window_height)
        ? strct->window_height - 1 : wall_bottom_pixel;
    i = ft_which_texture(strct, ray_angle);
    strct->color = strct->rgb_ceiling;
    ft_draw_line(strct, strct->rays.column_id,
        0,
        strct->rays.column_id,
        wall_top_pixel);
    // strct->color = 0xCBF997;
    ft_drtex(strct, wall_top_pixel, wall_bottom_pixel, wall_strip_height, i);
    // ft_draw_line(strct, strct->rays.column_id,
    //     wall_top_pixel,
    //     strct->rays.column_id,
    //     wall_bottom_pixel);
    strct->color = strct->rgb_floor;
    ft_draw_line(strct, strct->rays.column_id,
        wall_bottom_pixel,
        strct->rays.column_id,
        strct->window_height - 1);
}

void        ft_horizontal_check(t_vars *strct, double ray_angle)
{
    double  xintercept;
    double  yintercept;
    double  xstep;
    double  ystep;
    double  next_horz_touch_x;
    double  next_horz_touch_y;
    int     found_horizontal_wall_hit;
    double  x_to_check;
    double  y_to_check;
    
    found_horizontal_wall_hit = 0;

    //////////////////////////////////////////////
    ////HORIZONTAL RAY-GRID INTERSECTION CHECK////
    //////////////////////////////////////////////

    //find the y-coordinate of the closest horizontal grid intersection
    yintercept = (floor(strct->player.y / strct->tile_y)) * strct->tile_y;
    yintercept += strct->rays.is_facing_down ? strct->tile_y : 0;
    //find the x-coordinate of the closes horizontal grid intersection
    xintercept = strct->player.x + ((yintercept - strct->player.y) / tan(ray_angle));

    //calculate increment xstep and ystep
    ystep = strct->tile_y;
    ystep *= strct->rays.is_facing_up ? -1 : 1;
    
    xstep = strct->tile_y / tan(ray_angle);
    xstep *= (strct->rays.is_facing_left && xstep > 0) ? -1 : 1;
    xstep *= (strct->rays.is_facing_right && xstep < 0) ? -1 : 1;

    next_horz_touch_x = xintercept;
    next_horz_touch_y = yintercept;

    //increment xstep and ystep until we find a wall
    while (next_horz_touch_x >= 0 && next_horz_touch_x <= strct->window_width
            && next_horz_touch_y >= 0 && next_horz_touch_y <= strct->window_height)
    {
        x_to_check = next_horz_touch_x;
        y_to_check = next_horz_touch_y + (strct->rays.is_facing_up ? -1 : 0);
        if (ft_has_wall_at(strct, x_to_check, y_to_check))
        {
            //found wall hit
            found_horizontal_wall_hit = 1;
            strct->rays.horz_wall_hit_x = next_horz_touch_x;
            strct->rays.horz_wall_hit_y = next_horz_touch_y;
            break;
        }
        else
        {
            next_horz_touch_x += xstep;
            next_horz_touch_y += ystep;
        }
    }
    //calculate the horizontal distance
    strct->rays.horz_hit_distance = (found_horizontal_wall_hit)
        ? ft_distance_between_points(strct->player.x, strct->player.y,
            strct->rays.horz_wall_hit_x, strct->rays.horz_wall_hit_y) : 2147483646;
}

void        ft_vertical_check(t_vars *strct, double ray_angle)
{
    double  xintercept;
    double  yintercept;
    double  xstep;
    double  ystep;
    double  next_vert_touch_x;
    double  next_vert_touch_y;
    int     found_vertical_wall_hit;
    double  x_to_check;
    double  y_to_check;
    
    //////////////////////////////////////////////
    /////VERTICAL RAY-GRID INTERSECTION CHECK/////
    //////////////////////////////////////////////
    
    found_vertical_wall_hit = 0;
    //find the x-coordinate of the closes vertical grid intersection
    xintercept = (floor(strct->player.x / strct->tile_x)) * strct->tile_x;
    xintercept += strct->rays.is_facing_right ? strct->tile_x : 0;
    //find the y-coordinate of the closes vertical grid intersection
    yintercept = strct->player.y + ((xintercept - strct->player.x) * tan(ray_angle));

    //calculate increment xstep and ystep
    xstep = strct->tile_x;
    xstep *= strct->rays.is_facing_left ? -1 : 1;
    
    ystep = strct->tile_x * tan(ray_angle);
    ystep *= (strct->rays.is_facing_up && ystep > 0) ? -1 : 1;
    ystep *= (strct->rays.is_facing_down && ystep < 0) ? -1 : 1;

    next_vert_touch_x = xintercept;
    next_vert_touch_y = yintercept;

    //increment xstep and ystep until we find a wall
    while (next_vert_touch_x >= 0 && next_vert_touch_x <= strct->window_width
            && next_vert_touch_y >= 0 && next_vert_touch_y <= strct->window_height)
    {
        x_to_check = next_vert_touch_x + (strct->rays.is_facing_left ? -1 : 0);
        y_to_check = next_vert_touch_y;
        if (ft_has_wall_at(strct, x_to_check, y_to_check))
        {
            //found wall hit
            found_vertical_wall_hit = 1;
            strct->rays.vert_wall_hit_x = next_vert_touch_x;
            strct->rays.vert_wall_hit_y = next_vert_touch_y;
            break;
        }
        else
        {
            next_vert_touch_x += xstep;
            next_vert_touch_y += ystep;
        }
    }
    //calculate the vertical distance
    strct->rays.vert_hit_distance = (found_vertical_wall_hit)
        ? ft_distance_between_points(strct->player.x, strct->player.y,
            strct->rays.vert_wall_hit_x, strct->rays.vert_wall_hit_y) : 2147483646;
}

void        ft_distance_calc(t_vars *strct, double ray_angle)
{
    ft_horizontal_check(strct, ray_angle);
    ft_vertical_check(strct, ray_angle);
    //only store the smallest of the distances
    strct->rays.wall_hit_x = (strct->rays.horz_hit_distance < strct->rays.vert_hit_distance)
        ? strct->rays.horz_wall_hit_x : strct->rays.vert_wall_hit_x;
    strct->rays.wall_hit_y = (strct->rays.horz_hit_distance < strct->rays.vert_hit_distance)
        ? strct->rays.horz_wall_hit_y : strct->rays.vert_wall_hit_y;
    strct->rays.distance = (strct->rays.horz_hit_distance < strct->rays.vert_hit_distance)
        ? strct->rays.horz_hit_distance : strct->rays.vert_hit_distance;
    strct->rays.was_hit_vertical = (strct->rays.vert_hit_distance < strct->rays.horz_hit_distance);
	strct->wall_distances[strct->rays.column_id] = strct->rays.distance;
}

void        cast_all_rays(t_vars *strct)
{
    double  ray_angle;
    strct->rays.column_id = 0;

    strct->player.rotation_angle = ft_normalize_angle(strct->player.rotation_angle);
    ray_angle = strct->player.rotation_angle - (strct->player.fov_angle / 2);
    while (strct->rays.column_id < strct->rays.num_of){
        ray_angle = ft_normalize_angle(ray_angle);
        strct->rays.is_facing_down = (ray_angle > 0 ) && (ray_angle < PI);
        strct->rays.is_facing_up = (strct->rays.is_facing_down == 0) ? 1 : 0;
        strct->rays.is_facing_right = (ray_angle < (PI / 2)) || (ray_angle > (1.5 * PI));
        strct->rays.is_facing_left = (strct->rays.is_facing_right == 0) ? 1 : 0;
        ft_distance_calc(strct, ray_angle);
        ray_angle += strct->player.fov_angle / strct->rays.num_of;
        strct->color = 0xCBC3E3;
        ft_draw_line(strct, ((strct->player.x + (strct->player.width / 2)) * strct->minimap_scale),
            ((strct->player.y + (strct->player.height / 2)) * strct->minimap_scale),
            (strct->rays.wall_hit_x * strct->minimap_scale),
            (strct->rays.wall_hit_y * strct->minimap_scale));
        strct->rays.column_id++;
    }
}

void        cast_3d_rays(t_vars *strct)
{
    double  ray_angle;
    strct->rays.column_id = 0;

    strct->player.rotation_angle = ft_normalize_angle(strct->player.rotation_angle);
    ray_angle = strct->player.rotation_angle - (strct->player.fov_angle / 2);
    while (strct->rays.column_id < strct->rays.num_of){
        ray_angle = ft_normalize_angle(ray_angle);
        strct->rays.is_facing_down = (ray_angle > 0 ) && (ray_angle < PI);
        strct->rays.is_facing_up = (strct->rays.is_facing_down == 0) ? 1 : 0;
        strct->rays.is_facing_right = (ray_angle < (PI / 2)) || (ray_angle > (1.5 * PI));
        strct->rays.is_facing_left = (strct->rays.is_facing_right == 0) ? 1 : 0;
        ft_distance_calc(strct, ray_angle);
        ft_render_3d_rays(strct, ray_angle);
        ray_angle += strct->player.fov_angle / strct->rays.num_of;
        strct->rays.column_id++;
    }
}