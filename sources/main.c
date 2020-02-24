/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:37:21 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/24 14:19:53 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_image(t_env *e)
{
	if (!(e->mlx.new_image = mlx_new_image(e->mlx.ptr,
					e->axes.axe_x, e->axes.axe_y)))
	{
		printf("Error\nmlx_new_image");
		ft_exit(e);
	}
	if (!(e->mlx.get_data = (int *)mlx_get_data_addr(e->mlx.new_image,
			&e->mlx.bits_per_pixel, &e->mlx.size_line, &e->mlx.endian)))
	{
		printf("Error\nmlx_get_data_addr");
		ft_exit(e);
	}
	if (!(e->spt.dist_wall = ft_calloc(sizeof(double), e->axes.axe_x)))
	{
		printf("Error\nMalloc e->spt.dist_wall");
		ft_exit(e);
	}
	ft_raycasting(e);
	ft_sprite(e);
	mlx_put_image_to_window(e->mlx.ptr, e->mlx.win_ptr,
			e->mlx.new_image, 0, 0);
	mlx_destroy_image(e->mlx.ptr, e->mlx.new_image);
}

void	ft_open_window(t_env *e)
{
	if (!(e->mlx.ptr = mlx_init()))
	{
		printf("Error\nmlx_init");
		ft_exit(e);
	}
	if (!(e->mlx.win_ptr = mlx_new_window(e->mlx.ptr, e->axes.axe_x,
			e->axes.axe_y, "Cub3d")))
	{
		printf("Error\nmlx_new_window");
		ft_exit(e);
	}
	ft_textures(e);
	ft_init_sprite(e);
	ft_init_image(e);
	mlx_do_key_autorepeatoff(e->mlx.ptr);
	mlx_hook(e->mlx.win_ptr, 2, 0, &ft_key_down, e);
	mlx_hook(e->mlx.win_ptr, 3, 0, &ft_key_up, e);
	mlx_hook(e->mlx.win_ptr, 17, 0, &ft_exit, e);
	mlx_loop_hook(e->mlx.ptr, &ft_deplacement, e);
	mlx_loop(e->mlx.ptr);
}

int		ft_exit(t_env *e)
{
	if (e->mlx.ptr && e->mlx.win_ptr)
	{
		mlx_clear_window(e->mlx.ptr, e->mlx.win_ptr);
		mlx_destroy_window(e->mlx.ptr, e->mlx.win_ptr);
	}
	if (e->sprite)
		free(e->sprite);
	if (e->map.buff)
		free(e->map.buff);
	system("leaks Cub3D");
	exit(0);
	return (0);
}

void	ft_push_bmp(t_env *e)
{
	e->mlx.ptr = mlx_init();
	e->mlx.win_ptr = mlx_new_window(e->mlx.ptr, e->axes.axe_x,
			e->axes.axe_y, "Cub3d");
	if (!(e->sprite = (t_sprite*)ft_calloc(sizeof(t_sprite), e->map.nbr_sprite)))
	{
		printf("Error\nMalloc sprite");
		ft_exit(e);
	}
	ft_textures(e);
	ft_init_sprite(e);
	e->mlx.new_image = mlx_new_image(e->mlx.ptr, e->axes.axe_x, e->axes.axe_y);
	e->mlx.get_data = (int *)mlx_get_data_addr(e->mlx.new_image,
			&e->mlx.bits_per_pixel, &e->mlx.size_line, &e->mlx.endian);
	if (!(e->spt.dist_wall = ft_calloc(sizeof(double), e->axes.axe_x)))
	{
		printf("Error\nMalloc e->spt.dist_wall");
		ft_exit(e);
	}
	ft_raycasting(e);
	ft_sprite(e);
	ft_bmp(e);
	ft_exit(e);
}

int		main(int argc, char **argv)
{
	t_env	e;
	int		len;

	ft_bzero(&e, sizeof(t_env));
	if (argc < 2 || argc > 3)
	{
		printf("Error\nargc");
		ft_exit(&e);
	}
	len = (ft_strlen(argv[1]) - 4);
	ft_read_map(argv, &e);
	ft_check_wall(&e);
	ft_check_resolution(&e);
	if (argv[2] && !ft_strncmp(argv[2], "--save", 6))
		ft_push_bmp(&e);
	if (!argv[1] || (ft_strncmp(argv[1] + len, ".cub", 4)))
	{
		printf("Error\nNo map or no file .cub");
		ft_exit(&e);
	}
	if (!(e.sprite = (t_sprite*)ft_calloc(sizeof(t_sprite), e.map.nbr_sprite)))
	{
		printf("Error\nMalloc sprite");
		ft_exit(&e);
	}
	ft_open_window(&e);
}
