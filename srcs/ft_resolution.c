/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfranco- <nfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:04:17 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/19 16:40:14 by nfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int         ft_split_numbers(char *str, int i, char **width, char **height)
{
    int     len_height;
    int     len_width;
    int     j;

    len_height = 0;
    len_width = 0;
    while (str[i] == ' ' && str[i] != '\0')
        i++;
    j = i;
    while (str[i++] != ' ' && str[i] != '\0')
        len_width++;
    *width = ft_substr(str, j, len_width);
    while (str[i] == ' ' && str[i] != '\0')
        i++;
    j = i;
    while (str[i++] != ' ' && str[i] != '\0')
        len_height++;
    *height = ft_substr(str, j, len_height + 1);
    return (0);
}

int         ft_validate_numbers(char *width, char *height)
{
    int     i;

    i = 0;
    while (width[i] != '\0')
    {
        if (ft_isdigit(width[i]) == 0)
            return (-1);
        i++;
    }
    i = 0;
    while (height[i] != '\0')
    {
        if (ft_isdigit(height[i]) == 0)
            return (-1);
        i++;
    }
    return (0);
}

int		ft_free_h_w(char *width, char *height)
{
	free(height);
    free(width);
	return (-1);
}

int         ft_resolution(char *str, t_vars *strct)
{
    int     screen_height;
    int     screen_width;
    char    *width;
    char    *height;
    int     i;

    i = 1;
    mlx_get_screen_size(strct->mlx, &screen_width, &screen_height);
    ft_split_numbers(str, i, &width, &height);
    if (ft_validate_numbers(width, height) == -1)
        return (ft_free_h_w(width, height));
    strct->window_width = ft_atoi(width);
    strct->window_height = ft_atoi(height);
    if ((strct->window_width > screen_width)
        || (strct->window_height > screen_height))
        {
        ft_putendl_fd("Your window is too big!!!", 1);
        return (ft_free_h_w(width, height));
    }
    return (ft_free_h_w(width, height) * 0);
}