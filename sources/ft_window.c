/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:13:29 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/12 20:58:08 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_raycasting(t_env *e, int x)
{
	e->map.camera_x = 2 * x / (double)(e->axes.axe_x) - 1;
	e->map.ray_dir_x = e->orientation.dir_x + e->map.plan_x * e->map.camera_x;
	e->map.ray_dir_y = e->orientation.dir_y + e->map.plan_y * e->map.camera_x;
	e->raycasting.delta_x = fabs(1 / e->map.ray_dir_x);
	e->raycasting.delta_y = fabs(1 / e->map.ray_dir_y);
	e->raycasting.map_x = (int)e->map.pos_n_x;
	e->raycasting.map_y = (int)e->map.pos_n_y;
}

void	ft_raycasting_first(t_env *e)
{
	if (e->map.ray_dir_x < 0)
		{
			e->raycasting.step_x = -1;
			e->raycasting.side_dist_x = (e->map.pos_n_x - e->raycasting.map_x) * e->raycasting.delta_x;
		}
		else
		{
			e->raycasting.step_x = 1;
			e->raycasting.side_dist_x = (e->raycasting.map_x + 1.0 - e->map.pos_n_x) * e->raycasting.delta_x;
		}
		if (e->map.ray_dir_y < 0)
		{	
			e->raycasting.step_y = -1;
			e->raycasting.side_dist_y = (e->map.pos_n_y - e->raycasting.map_y) * e->raycasting.delta_y;
		}
		else
		{
			e->raycasting.step_y = 1;
			e->raycasting.side_dist_y = (e->raycasting.map_y + 1.0 - e->map.pos_n_y) * e->raycasting.delta_y;
		}
}

void	ft_no_wall(int hit, t_env *e)
{
	while (hit == 0)
	{
		if (e->raycasting.side_dist_x < e->raycasting.side_dist_y)
		{	
			e->raycasting.side_dist_x += e->raycasting.delta_x;
			e->raycasting.map_x += e->raycasting.step_x;
			e->raycasting.side = 0;
		}
		else
		{	
			e->raycasting.side_dist_y += e->raycasting.delta_y;
			e->raycasting.map_y += e->raycasting.step_y;
			e->raycasting.side = 1;
		}
		if (e->map.tab_map[e->raycasting.map_y][e->raycasting.map_x] == '1')
			hit = 1;
	}
}

void	ft_colonne(t_env *e, int x)
{
	e->map.hauteur_line = (e->axes.axe_y / e->raycasting.perp_wall_dist);
	e->map.draw_start = -e->map.hauteur_line / 2 + e->axes.axe_y / 2;
	e->map.draw_end = e->map.hauteur_line / 2 + e->axes.axe_y / 2;
	if (e->map.draw_start < 0)
		e->map.draw_start = 0;
	if (e->map.draw_end >= e->axes.axe_y)
		e->map.draw_end = e->axes.axe_y - 1;
		ft_put_textures(e, x);
}

void	ft_sol_plafond(t_env *e, int x, int y)
{
	y = 0;
	if (e->map.draw_end < 0)
			 e->map.draw_end = e->axes.axe_y;
		y = e->map.draw_end;
		while (y < e->axes.axe_y)
		{
			e->mlx.get_data[x + y * (e->mlx.size_line / 4)] = e->colors.color_sol;
			e->mlx.get_data[x + (e->axes.axe_y - y - 1) * (e->mlx.size_line / 4)] = e->colors.color_plafond;
			y++;
		}
}

void	ft_raycasting(t_env *e)
{
	int	x;
	int	hit;
	int	y;

	x = 0;
	hit = 0;
	y = 0;
	while (x < e->axes.axe_x)
	{
		ft_init_raycasting(e, x);
		ft_raycasting_first(e);
		hit = 0;
		ft_no_wall(hit, e);
		if (e->raycasting.side == 0)
			e->raycasting.perp_wall_dist = (e->raycasting.map_x - e->map.pos_n_x + (1 - e->raycasting.step_x) / 2) / e->map.ray_dir_x;
		else
			e->raycasting.perp_wall_dist = (e->raycasting.map_y - e->map.pos_n_y + (1 - e->raycasting.step_y) / 2) / e->map.ray_dir_y;
		ft_color_wall(e);
		ft_colonne(e, x);
		ft_sol_plafond(e, x, y);
	x++;
	}
}
int	ft_exit(t_env *e)
{
	(void)e;
	exit(0);
	return (0);
}

void	ft_init_image(t_env *e)
{
	e->mlx.new_image = mlx_new_image(e->mlx.ptr, e->axes.axe_x, e->axes.axe_y);
	e->mlx.get_data = (int *)mlx_get_data_addr(e->mlx.new_image, &e->mlx.bits_per_pixel, &e->mlx.size_line, &e->mlx.endian);
	ft_raycasting(e);
	mlx_put_image_to_window (e->mlx.ptr, e->mlx.win_ptr, e->mlx.new_image, 0, 0);
	mlx_destroy_image(e->mlx.ptr, e->mlx.new_image);
}

void	ft_open_window(t_env *e)
{
	e->mlx.ptr = mlx_init();
	e->mlx.win_ptr = mlx_new_window(e->mlx.ptr, e->axes.axe_x, e->axes.axe_y, "Cub3d");
	ft_textures(e);
	ft_init_image(e);
	mlx_do_key_autorepeatoff(e->mlx.ptr);
	mlx_hook(e->mlx.win_ptr, 2, 0, &ft_key_down, e);
	mlx_hook(e->mlx.win_ptr, 3, 0, &ft_key_up, e);
	mlx_hook(e->mlx.win_ptr, 17, 0, &ft_exit, e);
	mlx_loop_hook(e->mlx.ptr, &ft_deplacement, e);
	mlx_loop(e->mlx.ptr);
}
