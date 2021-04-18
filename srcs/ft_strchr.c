/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:08:25 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/24 19:53:00 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char		*ft_strchr(const char *s, int c)
{
	char	*st;

	while (*s != '\0')
	{
		if (*s == c)
		{
			st = (char *)s;
			return (st);
		}
		s++;
	}
	st = (char *)s;
	if (c == '\0')
		return (st);
	return (0);
}
