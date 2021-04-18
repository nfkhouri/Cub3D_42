/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadoglio <gadoglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 22:15:25 by gadoglio          #+#    #+#             */
/*   Updated: 2021/03/25 21:37:08 by gadoglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

int		ft_strlen_gnl(char *str);
char	*ft_substr_gnl(char *s, int start, int end);
char	*ft_strjoin(char *s1, char *s2);
int		find_char(char *str, char c);
int		get_next_line(int fd, char **line);
int		ft_do_rest(char **rest, char **final, char **line);
char	*ft_calloc(int size);

#endif