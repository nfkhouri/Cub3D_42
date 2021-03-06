/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:05:15 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/22 21:23:00 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int		ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	negative;

	nbr = 0;
	negative = 1;
	i = 0;
	while ((str[i] >= 8 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			negative *= -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= '0') && (str[i] <= '9'))
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	return (nbr * negative);
}
