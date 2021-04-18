/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:21:52 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/22 22:05:19 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

size_t		ft_strlen(const char *str)
{
	size_t i;
	size_t length;

	i = 0;
	length = 0;
	while (str[i++] != '\0')
	{
		length++;
	}
	return (length);
}
