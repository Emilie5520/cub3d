/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:47:38 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/25 12:09:04 by edouvier         ###   ########.fr       */
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
