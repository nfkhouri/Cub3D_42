/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:00:22 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/08 13:47:25 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int key_press(int keycode, t_vars *strct)
{
    //if the UP or 'w' keys have been pressed
    if (keycode == 65362 || keycode == 119)
        strct->player.walk_direction = 1;
    //if the DOWN or 's' keys have been pressed
    if (keycode == 65364 || keycode == 115)
        strct->player.walk_direction = -1;
    //if the LEFT or 'a' keys have been pressed
    if (keycode == 65361)
        strct->player.turn_direction = -1;
    //if the RIGHT or 'd' keys have been pressed
    if (keycode == 65363)
        strct->player.turn_direction = 1;
	if (keycode == 100)
		strct->player.is_mov_right = -1;
	if (keycode == 97)
		strct->player.is_mov_right = 1;
    //if the 'esc' key has been pressed the program closes.
    if (keycode == 65307)
    {
        mlx_destroy_window(strct->mlx, strct->mlx_win);
        close_program(strct);
    }
    return (0);
}
int key_release(int keycode, t_vars *strct)
{
    //if the UP or 'w' keys have been pressed
    if (keycode == 65362 || keycode == 119)
        strct->player.walk_direction = 0;
    //if the DOWN or 's' keys have been pressed
    if (keycode == 65364 || keycode == 115)
        strct->player.walk_direction = 0;
    //if the LEFT or 'a' keys have been pressed
    if (keycode == 65361)
        strct->player.turn_direction = 0;
    //if the RIGHT or 'd' keys have been pressed
    if (keycode == 65363)
        strct->player.turn_direction = 0;
	if (keycode == 97 || keycode == 100)
		strct->player.is_mov_right = 0;
    return (0);
}