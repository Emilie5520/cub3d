/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deplacements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:37:58 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/19 20:21:00 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		ft_deplacement_left(t_env *e)
{
	if (e->mvt.left == 1)
	{
		if ((e->map.tab_map[(int)(e->map.pos_n_y - e->map.plan_y * 0.2)]
				[(int)(e->map.pos_n_x)] != '1') && (e->map.tab_map[(int)(e->map.pos_n_y
					- e->map.plan_y * 0.2)]	[(int)(e->map.pos_n_x)] != '2'))
			e->map.pos_n_y -= e->map.plan_y * 0.2;
		if ((e->map.tab_map[(int)(e->map.pos_n_y)][(int)(e->map.pos_n_x - e->map.plan_x * 0.2)]
					!= '1') && (e->map.tab_map[(int)(e->map.pos_n_y)][(int)(e->map.pos_n_x
							- e->map.plan_x * 0.2)] != '2'))
			e->map.pos_n_x -= e->map.plan_x * 0.2;
	}
	if (e->mvt.rot_left == 1)
	{
		e->mvt.old_dir_x = e->orientation.dir_x;
		e->orientation.dir_x = e->orientation.dir_x * cos(-e->mvt.vit_rot)
			- e->orientation.dir_y * sin(-e->mvt.vit_rot);
		e->orientation.dir_y = e->mvt.old_dir_x * sin(-e->mvt.vit_rot)
			+ e->orientation.dir_y * cos(-e->mvt.vit_rot);
		e->mvt.old_plan_x = e->map.plan_x;
		e->map.plan_x = e->map.plan_x * cos(-e->mvt.vit_rot) -
			e->map.plan_y * sin(-e->mvt.vit_rot);
		e->map.plan_y = e->mvt.old_plan_x * sin(-e->mvt.vit_rot) +
			e->map.plan_y * cos(-e->mvt.vit_rot);
	}
}

void		ft_deplacement_right(t_env *e)
{
	if (e->mvt.rot_right == 1)
	{
		e->mvt.old_dir_x = e->orientation.dir_x;
		e->orientation.dir_x = e->orientation.dir_x * cos(e->mvt.vit_rot) -
			e->orientation.dir_y * sin(e->mvt.vit_rot);
		e->orientation.dir_y = e->mvt.old_dir_x * sin(e->mvt.vit_rot) +
			e->orientation.dir_y * cos(e->mvt.vit_rot);
		e->mvt.old_plan_x = e->map.plan_x;
		e->map.plan_x = e->map.plan_x * cos(e->mvt.vit_rot) -
			e->map.plan_y * sin(e->mvt.vit_rot);
		e->map.plan_y = e->mvt.old_plan_x * sin(e->mvt.vit_rot) +
			e->map.plan_y * cos(e->mvt.vit_rot);
	}
	if (e->mvt.right == 1)
	{
		if ((e->map.tab_map[(int)(e->map.pos_n_y)][(int)(e->map.plan_x * 0.2 +
					e->map.pos_n_x)] != '1') &&
		 ((e->map.tab_map[(int)(e->map.pos_n_y)][(int)(e->map.plan_x * 0.2 +
					e->map.pos_n_x)] != '2')))
			e->map.pos_n_x += e->map.plan_x * 0.2;
		if ((e->map.tab_map[(int)(e->map.pos_n_y + e->map.plan_y * 0.2)]
				[(int)(e->map.pos_n_x)] != '1')
				&& ((e->map.tab_map[(int)(e->map.pos_n_y + e->map.plan_y * 0.2)]
					[(int)(e->map.pos_n_x)] != '2')))
			e->map.pos_n_y += e->map.plan_y * 0.2;
	}
}

void		ft_deplacement_down(t_env *e)
{
	if (e->mvt.down == 1)
	{
		if ((e->map.tab_map[(int)(e->map.pos_n_y - e->orientation.dir_y * 0.2)]
				[(int)(e->map.pos_n_x)] != '1')
		&& (e->map.tab_map[(int)(e->map.pos_n_y - e->orientation.dir_y * 0.2)]
				[(int)(e->map.pos_n_x)] != '2'))
			e->map.pos_n_y -= e->orientation.dir_y * 0.2;
		if ((e->map.tab_map[(int)(e->map.pos_n_y)]
				[(int)(e->map.pos_n_x - e->orientation.dir_x * 0.2)] != '1')
		&& (e->map.tab_map[(int)(e->map.pos_n_y)]
				[(int)(e->map.pos_n_x - e->orientation.dir_x * 0.2)] != '2'))
			e->map.pos_n_x -= e->orientation.dir_x * 0.2;
	}
}

int		ft_deplacement(t_env *e)
{
	double tmp;

	tmp = e->map.pos_n_x + e->map.pos_n_y + e->map.plan_x + e->map.plan_y;
	e->mvt.vit_rot = 0.08;
	if (e->mvt.up == 1)
	{
		if ((e->map.tab_map[(int)(e->map.pos_n_y)]
				[(int)(e->map.pos_n_x + e->orientation.dir_x * 0.2)] != '1')
		&& (e->map.tab_map[(int)(e->map.pos_n_y)]
				[(int)(e->map.pos_n_x + e->orientation.dir_x * 0.2)] != '2'))
			e->map.pos_n_x += e->orientation.dir_x * 0.2;
		if ((e->map.tab_map[(int)(e->map.pos_n_y + e->orientation.dir_y * 0.2)]
				[(int)(e->map.pos_n_x)] != '1')
		&& (e->map.tab_map[(int)(e->map.pos_n_y + e->orientation.dir_y * 0.2)]
				[(int)(e->map.pos_n_x)] != '2'))
			e->map.pos_n_y += e->orientation.dir_y * 0.2;
	}
	ft_deplacement_down(e);
	ft_deplacement_left(e);
	ft_deplacement_right(e);
	if (tmp != e->map.pos_n_x + e->map.pos_n_y + e->map.plan_x + e->map.plan_y)
		ft_init_image(e);
	return (0);
}
