/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:47:45 by gadoglio          #+#    #+#             */
/*   Updated: 2021/04/14 19:48:21 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int         ft_split_path(char *str, char **path)
{
    int     len_path;
    int     i;
    int     j;

    i = 2;
    len_path = 0;
    while ((str[i] == ' ' || str[i] == ',') && str[i] != '\0')
        i++;
    j = i;
    while ((str[i++] != ' ' && str[i] != ',') && str[i] != '\0')
        len_path++;
    *path = ft_substr(str, j, len_path + 1);
    return (0);
}

int         ft_path_check(char *path)
{
   //CHECK IF PATH OPENS
    int     fd;
    //when extension is .txt da erro na horaq de fechar o programa
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        ft_putendl_fd("Invalid path to texture!", 1);
        return (-1);
    }
    close(fd);
    return (0);
}

int         ft_textures(char *str, t_vars *strct)
{
    char    *path;

    ft_split_path(str, &path);
    if (ft_path_check(path) < 0)
    {
        free(path);
        return (-1);
    }
    if (str[0] == 'N')
        strct->tex_path[0] = ft_strdup(path);
    else if (str[0] == 'W')
        strct->tex_path[3] = ft_strdup(path);
    else if (str[0] == 'E')
        strct->tex_path[2] = ft_strdup(path);
    else
    {
        if (str[1] == 'O')
            strct->tex_path[1] = ft_strdup(path);
        else
            strct->tex_path[4] = ft_strdup(path);
    }
    free(path);
    return (0);
}