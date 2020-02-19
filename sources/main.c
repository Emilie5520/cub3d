/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:37:21 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/19 13:15:19 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_image(t_env *e)
{
	e->mlx.new_image = mlx_new_image(e->mlx.ptr, e->axes.axe_x, e->axes.axe_y);
	e->mlx.get_data = (int *)mlx_get_data_addr(e->mlx.new_image,
			&e->mlx.bits_per_pixel, &e->mlx.size_line, &e->mlx.endian);
	ft_raycasting(e);
	mlx_put_image_to_window(e->mlx.ptr, e->mlx.win_ptr,
			e->mlx.new_image, 0, 0);
	mlx_destroy_image(e->mlx.ptr, e->mlx.new_image);
}

void	ft_open_window(t_env *e)
{
	e->mlx.ptr = mlx_init();
	e->mlx.win_ptr = mlx_new_window(e->mlx.ptr, e->axes.axe_x,
			e->axes.axe_y, "Cub3d");
	ft_textures(e);
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
	if (e->map.tab_map)
		free(e->map.tab_map);
	exit(0);
	return (0);
}

void	ft_push_bmp(t_env *e)
{
	e->mlx.ptr = mlx_init();
	e->mlx.win_ptr = mlx_new_window(e->mlx.ptr, e->axes.axe_x,
			e->axes.axe_y, "Cub3d");
	ft_textures(e);
	ft_init_sprite(e);
	e->mlx.new_image = mlx_new_image(e->mlx.ptr, e->axes.axe_x, e->axes.axe_y);
	e->mlx.get_data = (int *)mlx_get_data_addr(e->mlx.new_image,
			&e->mlx.bits_per_pixel, &e->mlx.size_line, &e->mlx.endian);
	e->spt.dist_wall = ft_calloc(sizeof(double*), e->axes.axe_x);
	ft_raycasting(e);
	ft_sprite(e);
	ft_bmp(e);
	ft_exit(e);
}

int		main(int argc, char **argv)
{
	t_env	e;

	(void)argc;
	ft_initialize_parsing(&e);
	ft_read_map(argv, &e);
	//ft_check_wall(&e);
	if (argv[2] && !ft_strncmp(argv[2], "--save", 6))
		ft_push_bmp(&e);
	e.sprite = (t_sprite*)ft_calloc(sizeof(t_sprite), e.map.nbr_sprite);
	ft_open_window(&e);
}
