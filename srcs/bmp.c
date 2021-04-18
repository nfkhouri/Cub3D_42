#include "../cub3D.h"
#include <sys/stat.h>

static void			little_endian_int(unsigned char *adr, unsigned int vl)
{
	adr[0] = (unsigned char)(vl);
	adr[1] = (unsigned char)(vl >> 8);
	adr[2] = (unsigned char)(vl >> 16);
	adr[3] = (unsigned char)(vl >> 24);
}

static int			store_color(t_vars *strct, int x, int y)
{
	unsigned int	color;
	unsigned char	addr_color[4];

	color = *(unsigned int *)(strct->addr + strct->window_width *
			(strct->window_height - y - 1) * 4 + x * 4);
	little_endian_int(&addr_color[0], color);
	return (*(unsigned int*)(addr_color));
}

static void			bmp_header(t_vars *strct, int fd)
{
	unsigned char	file[54];
	int				filesize;

	ft_bzero(&file, 54);
	filesize = 54 + strct->window_height * strct->window_width * strct->bits_per_pixel / 8;
	file[0] = (unsigned char)('B');
	file[1] = (unsigned char)('M');
	little_endian_int(&file[2], filesize);
	file[10] = (unsigned char)(54);
	file[14] = (unsigned char)(40);
	little_endian_int(&file[18], strct->window_width);
	little_endian_int(&file[22], strct->window_height);
	file[26] = (unsigned char)(1);
	file[28] = (unsigned char)(32);
	write(fd, &file, 54);
}

int					save_bmp_file(t_vars *strct)
{
	int				fd;
	int				bmp[strct->window_height][strct->window_width];
	int				x;
	int				y;

	if ((fd = open("photo.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR |
					S_IRGRP | S_IROTH, 777)) < 0)
		return (-1);
	bmp_header(strct, fd);
	y = 0;
	while (y < strct->window_height)
	{
		x = 0;
		while (x < strct->window_width)
		{
			bmp[y][x] = store_color(strct, x, y);
			write(fd, &bmp[y][x], 4);
			x++;
		}
		y++;
	}
	close(fd);
	return (0);
}