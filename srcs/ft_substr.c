/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:44:43 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/22 21:49:17 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	size = ft_strlen((char *)s);
	if (start > size)
		return (ft_strdup(""));
	if (!(new = (char *)malloc((sizeof(char) * (len + 1)))))
		return (0);
	i = 0;
	while (i < len && *s)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}
