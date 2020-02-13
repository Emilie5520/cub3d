/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:37:21 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/13 13:52:06 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	ft_exit(t_env *e)
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
	e->mlx.win_ptr = mlx_new_window(e->mlx.ptr, e->axes.axe_x, e->axes.axe_y, "Cub3d");
	ft_textures(e);
	e->mlx.new_image = mlx_new_image(e->mlx.ptr, e->axes.axe_x, e->axes.axe_y);
	e->mlx.get_data = (int *)mlx_get_data_addr(e->mlx.new_image, &e->mlx.bits_per_pixel, &e->mlx.size_line, &e->mlx.endian);
	ft_raycasting(e);
	ft_bmp(e);
	ft_exit(e);
}

int	main(int argc, char **argv)
{

	t_env e;

	(void)argc;	
	ft_initialize_parsing(&e);
	ft_read_map(argv, &e);
	if (argv[2] && !ft_strncmp(argv[2], "--save", 6))
		ft_push_bmp(&e);	
	ft_open_window(&e);
}
