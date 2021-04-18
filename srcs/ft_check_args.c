/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:40:05 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/19 20:19:06 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_check_argument(char *s)
{
	int		len;

    len = ft_strlen(s);
    if (len <= 4 || ft_strncmp(s + (len - 4), ".cub", 4) != 0)
    {
        ft_putendl_fd("Error: Invalid map file.", 1);
        return (-1);
    }
    return (0);
}

int		ft_check_args(t_vars *strct, int argc, char **argv)
{
	if (argc <= 1)
    {
        ft_putendl_fd("Error: Not enough arguments. This program needs a map file as an argument\n \
		USE: ./cub3d [mapfile.cub]", 1);
        return(1);
    }
	else if (argc == 2)
	{
		if (ft_check_argument(argv[1]) >= 0){
            strct->map_path = argv[1];
            return(0);
        }
	}
	else if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 6) != 0)
        {
            ft_putendl_fd("Error: Invalid flag as argument.\nUse: --save", 1);
            exit(1);
        }
        if (ft_strncmp(argv[2], "--save", 6) == 0)
		{
            strct->save = 1;
			strct->map_path = argv[1];
            return(0);
        }
	}
    ft_putendl_fd("Error: Invalid number of arguments", 1);
	exit(1);
}