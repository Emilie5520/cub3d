/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 10:18:06 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/19 12:20:58 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_header(unsigned char *header, int param)
{
	header[0] = (unsigned char)(param);
	header[1] = (unsigned char)(param >> 8);
	header[2] = (unsigned char)(param >> 16);
	header[3] = (unsigned char)(param >> 24);
}

void	ft_image_bmp(t_env *e, t_bmp *bmp)
{
	int i;
	int j;
	int x;
	int y;

	j = -1;
	while (++j < e->axes.axe_y)
	{
		i = -1;
		while (++i < e->axes.axe_x)
		{
			x = i;
			y = e->axes.axe_y - 1 - j;
			printf("color %d\n", bmp->color);
			printf("x %d\n", x);
			printf("y %d\n", y);
			printf("axe x %d\n", e->axes.axe_x);
			bmp->color = e->mlx.get_data[x + y * e->axes.axe_x];
			write(bmp->fd, &bmp->color, 3);
		}
		i = -1;
		while (++i < (4 - (e->axes.axe_x * 3) % 4) % 4)
			write(bmp->fd, &bmp->pad, 1);
	}
}

void	ft_complete_header(t_env *e, t_bmp *bmp)
{
	int	i;

	i = 0;
	while (i < 14)
		bmp->header[i++] = 0;
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	bmp->header[10] = 54;
	i = 0;
	while (i < 40)
		bmp->info[i++] = 0;
	bmp->info[0] = 40;
	bmp->info[12] = 1;
	bmp->info[14] = 24;
	i = 0;
	while (i < 3)
		bmp->pad[i++] = 0;
	set_header(&bmp->header[2], bmp->size);
	set_header(&bmp->info[4], e->axes.axe_x);
	set_header(&bmp->info[8], e->axes.axe_y);
	write(bmp->fd, bmp->header, 14);
	write(bmp->fd, bmp->info, 40);
}

void	ft_bmp(t_env *e)
{
	t_bmp	bmp;
	int		image_size;

	image_size = 3 * e->axes.axe_x * e->axes.axe_y;
	bmp.size = 54 + image_size;
	bmp.image = malloc((sizeof(char) * image_size));
	ft_memset(bmp.image, 0, image_size);
	bmp.fd = open("image.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	ft_complete_header(e, &bmp);
	ft_image_bmp(e, &bmp);
	free(bmp.image);
	close(bmp.fd);
}
