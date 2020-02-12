/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:37:58 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/10 16:40:39 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"


int	ft_key_down(int keycode, t_env *e)
{

	if (keycode == 13)
		e->mvt.up = 1;
	if (keycode == 1)
		e->mvt.down = 1;
	if (keycode == 2)
		e->mvt.right = 1;
	if (keycode == 0)
		e->mvt.left = 1;
	if (keycode == 14 || keycode == 124)
		e->mvt.rot_right = 1;
	if (keycode == 12 || keycode == 123)
		e->mvt.rot_left = 1;
	return (0);
}

int	ft_key_up(int keycode, t_env *e)
{
	if (keycode == 13)
		e->mvt.up = 0;
	if (keycode == 1)
		e->mvt.down = 0;
	if (keycode == 2)
		e->mvt.right = 0;
	if (keycode == 0)
		e->mvt.left = 0;
	if (keycode == 14 || keycode == 124)
		e->mvt.rot_right = 0;
	if (keycode == 12 || keycode == 123)
		e->mvt.rot_left = 0;
	if (keycode == 53)
		exit(1);
	return(0);
}

int	ft_deplacement(t_env *e)
{
	double tmp;

	tmp = e->map.pos_n_x + e->map.pos_n_y + e->map.plan_x + e->map.plan_y;
	e->mvt.vit_rot = 0.08;
	if (e->mvt.up == 1)
	{
		if (e->map.tab_map[(int)(e->map.pos_n_y)][(int)(e->map.pos_n_x + e->orientation.dir_x * 0.2)] != '1')
			e->map.pos_n_x += e->orientation.dir_x * 0.1;
		if (e->map.tab_map[(int)(e->map.pos_n_y + e->orientation.dir_y * 0.2)][(int)(e->map.pos_n_x)] != '1')
			e->map.pos_n_y += e->orientation.dir_y * 0.1;
	}
	if (e->mvt.down == 1)
	{
		if (e->map.tab_map[(int)(e->map.pos_n_y - e->orientation.dir_x * 0.2)][(int)(e->map.pos_n_x)] != '1')
			e->map.pos_n_x -= e->orientation.dir_x * 0.2;
		if (e->map.tab_map[(int)(e->map.pos_n_y)][(int)(e->map.pos_n_x - e->orientation.dir_y * 0.2)] != '1')
			e->map.pos_n_y -= e->orientation.dir_y * 0.2;
	}
	if (e->mvt.right == 1)
	{
		if (e->map.tab_map[(int)(e->map.pos_n_y + e->map.plan_x * 0.2)][(int)(e->map.pos_n_x)] != '1')
			e->map.pos_n_x += e->map.plan_x * 0.2;
		if (e->map.tab_map[(int)(e->map.pos_n_y)][(int)(e->map.pos_n_x + e->map.plan_y * 0.2)] != '1')
			e->map.pos_n_y += e->map.plan_y * 0.2;

	}
	if (e->mvt.left == 1)
	{	
		if (e->map.tab_map[(int)(e->map.pos_n_y - e->map.plan_x * 0.2)][(int)(e->map.pos_n_x)] != '1')
			e->map.pos_n_x -= e->map.plan_x * 0.2;
		if (e->map.tab_map[(int)(e->map.pos_n_y)][(int)(e->map.pos_n_x - e->map.plan_y * 0.2)] != '1')
			e->map.pos_n_y -= e->map.plan_y * 0.2;
	}
	if (e->mvt.rot_left == 1)
	{
		e->mvt.old_dir_x = e->orientation.dir_x;
		e->orientation.dir_x = e->orientation.dir_x * cos(-e->mvt.vit_rot) - e->orientation.dir_y * sin(-e->mvt.vit_rot);
		e->orientation.dir_y = e->mvt.old_dir_x * sin(-e->mvt.vit_rot) + e->orientation.dir_y * cos(-e->mvt.vit_rot);
		e->mvt.old_plan_x = e->map.plan_x;
		e->map.plan_x = e->map.plan_x * cos(-e->mvt.vit_rot) - e->map.plan_y * sin(-e->mvt.vit_rot);
		e->map.plan_y = e->mvt.old_plan_x * sin(-e->mvt.vit_rot) + e->map.plan_y * cos(-e->mvt.vit_rot);
	}
	if (e->mvt.rot_right == 1)
	{
		
		e->mvt.old_dir_x = e->orientation.dir_x;
		e->orientation.dir_x = e->orientation.dir_x * cos(e->mvt.vit_rot) - e->orientation.dir_y * sin(e->mvt.vit_rot);
		e->orientation.dir_y = e->mvt.old_dir_x * sin(e->mvt.vit_rot) + e->orientation.dir_y * cos(e->mvt.vit_rot);
		e->mvt.old_plan_x = e->map.plan_x;
		e->map.plan_x = e->map.plan_x * cos(e->mvt.vit_rot) - e->map.plan_y * sin(e->mvt.vit_rot);
		e->map.plan_y = e->mvt.old_plan_x * sin(e->mvt.vit_rot) + e->map.plan_y * cos(e->mvt.vit_rot);
	}
	if (tmp != e->map.pos_n_x + e->map.pos_n_y + e->map.plan_x + e->map.plan_y)
		ft_init_image(e);
	return (0);
}
