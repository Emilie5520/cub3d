/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:03:52 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/20 17:54:05 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_sprite_distance(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->map.nbr_sprite)
	{
		e->sprite[i].sprite_order = i;
		e->sprite[e->sprite[i].sprite_order].sprite_distance =
			ft_power(e->map.pos_n_x - e->sprite[e->sprite[i].
					sprite_order].coord.x, 2) +
			ft_power(e->map.pos_n_y - e->sprite[e->sprite[i].
					sprite_order].coord.y, 2);
		i++;
	}
}

void	ft_swap_sprite(t_env *e)
{
	int	i;
	int tmp;

	i = 0;
	while (i + 1 < e->map.nbr_sprite)
	{
		if (e->sprite[e->sprite[i].sprite_order].sprite_distance <
				e->sprite[e->sprite[i + 1].sprite_order].sprite_distance)
		{
			tmp = e->sprite[i].sprite_order;
			e->sprite[i].sprite_order = e->sprite[i + 1].sprite_order;
			e->sprite[i + 1].sprite_order = tmp;
			ft_swap_sprite(e);
		}
		i++;
	}
}

void	ft_pos_sprite(t_env *e, int i)
{

	e->spt.x = e->sprite[e->sprite[i].sprite_order].coord.x - e->map.pos_n_x;
	e->spt.y = e->sprite[e->sprite[i].sprite_order].coord.y - e->map.pos_n_y;
	e->spt.inv_det = 1.0 / (e->map.plan_x * e->orientation.dir_y -
			e->orientation.dir_x * e->map.plan_y);
	e->spt.transform_x = e->spt.inv_det * (e->orientation.dir_y *
			e->spt.x - e->orientation.dir_x * e->spt.y);
	e->spt.transform_y = e->spt.inv_det * (-e->map.plan_y * e->spt.x
			+ e->map.plan_x * e->spt.y);
	e->spt.screen_x = (int)((e->axes.axe_x / 2) * (1.0 + e->spt.transform_x /
			e->spt.transform_y));
	e->spt.height = abs((int)(e->axes.axe_y / e->spt.transform_y));
	e->spt.start_y = -e->spt.height / 2 + e->axes.axe_y / 2;
	if (e->spt.start_y < 0)
		e->spt.start_y = 0;
	e->spt.end_y = e->spt.height / 2 + e->axes.axe_y / 2;
	if (e->spt.end_y >= e->axes.axe_y)
		e->spt.end_y = e->axes.axe_y - 1;
	e->spt.width = abs((int)(e->axes.axe_y / e->spt.transform_y));
	e->spt.start_x = -e->spt.width / 2 + e->spt.screen_x;
	if (e->spt.start_x < 0)
		e->spt.start_x = 0;
	e->spt.end_x = e->spt.width / 2 + e->spt.screen_x;
	if (e->spt.end_x >= e->axes.axe_x)
		e->spt.end_x = e->axes.axe_x - 1;
}

void	ft_get_color(t_env *e, int i)
{
	if (e->sprite[i].image.get_data[e->spt.tex_x + e->spt.tex_y
			* e->sprite[i].image.w] != -16777216)
		e->sprite[i].image.color = e->sprite[i].image.get_data
			[e->spt.tex_x + e->spt.tex_y * e->sprite[i].image.w];
	else
		e->sprite[i].image.color = 0xBFD195;
}

void	ft_free_sprite(t_env *e)
{
	if (e->spt.dist_wall)
	{
		free(e->spt.dist_wall);
		e->spt.dist_wall = NULL;
	}
}

void	ft_sprite(t_env *e)
{
	int	i;
	int	x;
	int	y;
	long int	d;

	i = 0;
	ft_sprite_distance(e);
	ft_swap_sprite(e);
	while (i < e->map.nbr_sprite)
	{
		ft_pos_sprite(e, i);
		x = e->spt.start_x;
		while (x < e->spt.end_x && x < e->axes.axe_x)
		{
			e->spt.tex_x = (int)(256 * (x - (-e->spt.width / 2
						+ e->spt.screen_x)) * e->sprite[i].image.w /
				e->spt.width) / 256;

			if (e->spt.transform_y > 0)
			{
				y = e->spt.start_y;
				while (y < e->spt.end_y)
				{
					d = (y * 256 - e->axes.axe_y * 128 +  e->spt.height * 128);
					e->spt.tex_y = (d * e->sprite[i].image.h / e->spt.height) / 256;
					ft_get_color(e, i);
					if (e->sprite[i].image.color != 0xBFD195 && e->spt.transform_y < e->spt.dist_wall[x])
					{
						if (x >= 0 && x < e->axes.axe_x  && y >= 0 && y < e->axes.axe_y)
							e->mlx.get_data[x + y * (e->mlx.size_line / 4)] = e->sprite[i].image.color;
					}
					y++;
				}
			}
			x++;
		}
		i++;
	}
	ft_free_sprite(e);
}

void	ft_init_sprite(t_env *e)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
	while (e->map.tab_map[y])
	{
		x = 0;
		while (e->map.tab_map[y][x])
		{
			if (e->map.tab_map[y][x] == '2')
			{
				e->sprite[i].coord = (t_coord){x + 0.5, y + 0.5};
				i++;
			}
			x++;
		}
		y++;
	}
}
