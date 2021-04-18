/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:28:38 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/17 17:46:19 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void ft_render(t_vars *strct)
{
    ft_black_screen(strct);
    cast_3d_rays(strct);
	ft_render_sprites(strct);
    ft_render_map(strct);
    ft_render_player(strct);
    cast_all_rays(strct);
   	mlx_put_image_to_window(strct->mlx, strct->mlx_win, strct->img, 0, 0);
}

void ft_render_save(t_vars *strct)
{
    ft_black_screen(strct);
    cast_3d_rays(strct);
	ft_render_sprites(strct);
    ft_render_map(strct);
    ft_render_player(strct);
    cast_all_rays(strct);
	save_bmp_file(strct);
	exit(0);
}

// ////////////////////////////////////////////////////////////////////////////////

int ft_update(t_vars *strct)
{
    ft_move(strct);
    return (0);
}

////////////////////////////////////////////////////////////////////////////////

int ft_game(t_vars *strct) {
    ft_update(strct);
    ft_render(strct);
    return (0);
}

// ////////////////////////////////////////////////////////////////////////////////

int         main(int argc, char **argv)
{
    t_vars  strct;
    int     i;
    
    i = -1;
    strct.mlx = mlx_init();
    //initializes struct containing information regarding mlx and the window size
    ft_init_struct(&strct);
	if ((ft_check_args(&strct, argc, argv) < 0)
		|| (ft_check_input(&strct) < 0)
        || ft_check_map(&strct)){
        close_program(&strct);
        return(-1);
    }
    while (++i < 5)
        ft_load_textures(&strct, i);
	ft_init_rays(&strct);
	ft_init_image(&strct);
	if (strct.save == 1)
		ft_render_save(&strct);
	if (ft_init_window(&strct) == -1){
        printf("Error initializing window.");
        close_program(&strct);
    }
    mlx_hook(strct.mlx_win, 2, 1L<<0, key_press, &strct);
    mlx_hook(strct.mlx_win, 3, 1L<<1, key_release, &strct);
    mlx_hook(strct.mlx_win, 33, 1L<<17, close_program, &strct);
    
    //no idea what this does. I think it keeps the window open.
    mlx_loop_hook(strct.mlx, ft_game, &strct);
    mlx_loop(strct.mlx);
    
    return (0);    
}