/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:03:52 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/13 17:54:02 by edouvier         ###   ########.fr       */
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
		e->sprite[e->sprite[i].sprite_order].sprite_distance = ft_power(e->map.pos_n_x - e->sprite[e->sprite[i].sprite_order].coord.x, 2) + ft_power(e->map.pos_n_y - e->sprite[e->sprite[i].sprite_order].coord.y, 2);
		i++;
	}
}

void	ft_swap_sprite(t_env *e)
{
	int 	i;

	i = 0;
	while (i + 1 < e->map.nbr_sprite)
	{
		if (e->sprite[e->sprite[i].sprite_order].sprite_distance < 
				e->sprite[e->sprite[i + 1].sprite_order].sprite_distance)
			ft_swap(e->sprite[e->sprite[i].sprite_order].sprite_distance, e->sprite[e->sprite[i + 1].sprite_order].sprite_distance);
		i++;
	}
}

void	ft_draw_sprite(t_env *e)
{
	int	i;
	double	sprite_x;
	double	sprite_y;
	double 	inv_det;
	double	transform_x;
	double	transform_y;
	int	sprite_screen_x;
	
	i = 0;
	sprite_x = e->sprite[e->sprite[i].sprite_order].coord.x - e->map.pos_n_x; //pas sur
	sprite_y = e->sprite[e->sprite[i].sprite_order].coord.y - e->map.pos_n_y; //pas sur
	inv_det = 1.0 / (e->map.plan_x * e->orientation.dir_y - e->orientation.dir_x * e->map.plan_y);
	transform_x = inv_det * (e->orientation.dir_y * sprite_x - e->orientation.dir_x * sprite_y);
	transform_y = inv_det * (-e->map.plan_y * sprite_x + e->map.plan_x * sprite_y);
	sprite_screen_x = (e->axes.axe_y / 2) * (1 + transform_x / transform_y);

	while (i < e->map.nbr_sprite)
	{
		i++;
	}


}
