int         ft_distance_between_points(int x1, int y1, int x2, int y2){
    int     distance;

    distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return (distance);
}

////////////////////////////////////////////////////////////////////////////////

void     ft_cast_ray(t_vars *strct, int ray_angle){
    strct->ray.is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
    strct->ray.is_ray_facing_up = !strct->ray.is_ray_facing_down;

    strct->ray.is_ray_facing_right = ray_angle < (0.5 * PI) || ray_angle > (1.5 * PI);
    strct->ray.is_ray_facing_left = !strct->ray.is_ray_facing_right;
    
    double xintercept;
    double yintercept;
    double xstep;
    double ystep;
    
    //////////////////////////////////////////////
    ////HORIZONTAL RAY-GRID INTERSECTION CHECK////
    //////////////////////////////////////////////

    int     found_horz_hit = 0;
    double   horz_wall_hit_x = 0;
    double   horz_wall_hit_y = 0;
    int     horz_wall_content = 0;

    //Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(strct->player.playerY / strct->tile_Y) * strct->tile_Y;
    yintercept += strct->ray.is_ray_facing_down ? strct->tile_Y : 0;

    //Find the x-coordinate of the closest horizontal grid intersection
    xintercept = strct->player.playerX + ((yintercept - strct->player.playerY) / tan(ray_angle));

    //calculate the increment xtep and ystep
    ystep = strct->tile_Y;
    ystep *= strct->ray.is_ray_facing_up ? -1 : 1;

    xstep = strct->tile_X / tan(ray_angle);
    xstep *= (strct->ray.is_ray_facing_left && xstep > 0) ? -1 : 1;
    xstep *= (strct->ray.is_ray_facing_right && xstep < 0) ? -1 : 1;

    double next_horz_touch_x = xintercept;
    double next_horz_touch_y = yintercept;

    //increment xstep and ystep until we find a wall
    while (next_horz_touch_x >= 0 && next_horz_touch_x <= strct->window_width
        && next_horz_touch_y >= 0 && next_horz_touch_y <= strct->window_height) {
        double   x_to_check = next_horz_touch_x;
        double   y_to_check = next_horz_touch_y + (strct->ray.is_ray_facing_up ? -1 : 0);
        
        if (ft_has_wall_at(strct, x_to_check, y_to_check)) {
            found_horz_hit = 1;
            horz_wall_hit_x = next_horz_touch_x;
            horz_wall_hit_y = next_horz_touch_y;
            printf("next_horz_touch_x: %f\n", next_horz_touch_x);
            printf("next_horz_touch_y: %f\n\n", next_horz_touch_y);
            horz_wall_content = strct->map[(int)floor(y_to_check / strct->tile_Y)][(int)floor(x_to_check / strct->tile_X)];
            break;
        }
        else {
            next_horz_touch_x += xstep;
            next_horz_touch_y += ystep;
        }
    }

    //////////////////////////////////////////////
    ////VERTICAL RAY-GRID INTERSECTION CHECK////
    //////////////////////////////////////////////

    int     found_vert_hit = 0;
    double   vert_wall_hit_x = 0;
    double   vert_wall_hit_y = 0;
    int     vert_wall_content = 0;

    //Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(strct->player.playerX / strct->tile_X) * strct->tile_X;
    xintercept += strct->ray.is_ray_facing_right ? strct->tile_X : 0;

    //Find the y-coordinate of the closest vertical grid intersection
    yintercept = strct->player.playerY + ((xintercept - strct->player.playerX) * tan(ray_angle));

    //calculate the increment xtep and ystep
    xstep = strct->tile_X;
    xstep *= strct->ray.is_ray_facing_left ? -1 : 1;

    ystep = strct->tile_Y * tan(ray_angle);
    ystep *= (strct->ray.is_ray_facing_up && ystep > 0) ? -1 : 1;//
    ystep *= (strct->ray.is_ray_facing_down && ystep < 0) ? -1 : 1;//

    double next_vert_touch_x = xintercept;
    double next_vert_touch_y = yintercept;

    //increment xstep and ystep until we find a wall
    while (next_vert_touch_x >= 0 && next_vert_touch_x <= strct->window_width
        && next_vert_touch_y >= 0 && next_vert_touch_y <= strct->window_height) {
        double   x_to_check = next_vert_touch_x + (strct->ray.is_ray_facing_left ? -1 : 0);
        double   y_to_check = next_vert_touch_y;
        
        if (ft_has_wall_at(strct, x_to_check, y_to_check)) {
            printf("has wall");
            found_vert_hit = 1;
            vert_wall_hit_x = next_vert_touch_x;
            vert_wall_hit_y = next_vert_touch_y;
            vert_wall_content = strct->map[(int)floor(y_to_check / strct->tile_Y)][(int)floor(x_to_check / strct->tile_X)];
            break;
        }
        else {
            next_vert_touch_x += xstep;
            next_vert_touch_y += ystep;
        }
    }

    double      horz_hit_distance;
    double      vert_hit_distance;

    horz_hit_distance = found_horz_hit ?
        ft_distance_between_points(strct->player.playerX, strct->player.playerY, horz_wall_hit_x, horz_wall_hit_y) : 2147483646;
    
    vert_hit_distance = found_vert_hit ?
        ft_distance_between_points(strct->player.playerX, strct->player.playerY, vert_wall_hit_x, vert_wall_hit_y) : 2147483646;
    
    if (vert_hit_distance < horz_hit_distance){
        strct->ray.distance = vert_hit_distance;
        strct->ray.wall_hit_x = vert_wall_hit_x;
        strct->ray.wall_hit_y = vert_wall_hit_y;
        strct->ray.wall_hit_content = vert_wall_content;
        strct->ray.was_hit_vertical = 1;
    }
    else {
        strct->ray.distance = horz_hit_distance;
        strct->ray.wall_hit_x = horz_wall_hit_x;
        strct->ray.wall_hit_y = horz_wall_hit_y;
        strct->ray.wall_hit_content = horz_wall_content;
        strct->ray.was_hit_vertical = 0;
    }
    strct->ray.ray_angle = ray_angle;
}

////////////////////////////////////////////////////////////////////////////////

void    ft_render_ray(t_vars *strct){
    drawLine(strct, strct->minimap_scale * strct->player.playerX,
        strct->minimap_scale * strct->player.playerY,
        strct->minimap_scale * strct->ray.wall_hit_x,
        strct->minimap_scale * strct->ray.wall_hit_y);
}

////////////////////////////////////////////////////////////////////////////////

int     ft_cast_all_rays(t_vars *strct){
    double  ray_angle;
    int     strip_id;

    strip_id = 0;
    ray_angle = strct->player.rotation_angle - (strct->player.fov_angle / 2);
    ray_angle = ft_normalize_angle(ray_angle);
    strct->player.rotation_angle = ft_normalize_angle(strct->player.rotation_angle);
    ft_cast_ray(strct, ray_angle);
    ft_render_ray(strct);
    // while (strip_id < strct->num_of_rays){
    //     // ft_putnbr_fd(strip_id, 1);
    //     // ft_putnbr_fd("", 1);
    //     ft_cast_ray(strct, ray_angle);
    //     ray_angle += strct->player.fov_angle / strct->num_of_rays;
    //     if (strip_id ==992)
    //         printf("here");
    //     ft_render_ray(strct);
    //     strip_id++;
    // }
    return (0);
}

////////////////////////////////////////////////////////////////////////////////

void ft_render(t_vars *strct) {
    ft_black_screen(strct);
    ft_render_map(strct);
    ft_render_player(strct);
    ft_cast_all_rays(strct);
    mlx_put_image_to_window(strct->mlx, strct->mlx_win, strct->img, 0, 0);
}

// ////////////////////////////////////////////////////////////////////////////////

int ft_update(t_vars *strct) {
    // strct->player.turn_direction = -1;
    // strct->player.walk_direction = 1;
    ft_move(strct);
    return (0);
}

////////////////////////////////////////////////////////////////////////////////

int ft_game(t_vars *strct) {
    ft_update(strct);
    ft_render(strct);
    return (0);
}