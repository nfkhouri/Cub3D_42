/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:33:46 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/22 22:08:35 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char		*ft_strdup(const char *s1)
{
	size_t	size;
	size_t	i;
	char	*new;

	size = ft_strlen(s1);
	new = (char *)malloc((sizeof(char) * size) + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
