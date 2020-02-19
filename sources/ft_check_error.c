/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:08:51 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/19 16:48:50 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_check_wall_next(t_env *e)
{
	int	i;
	int	j;

	j = 0;
	i = e->raycasting.x;
	while (e->map.tab_map[i][j])
	{
		if (e->map.tab_map[i][j] != '1')
		{
			printf("Error map\nOnly '1' on the edges of your map");
			ft_exit(e);
		}
		j++;
	}
	i = e->raycasting.y;
	j = 0;
	while (e->map.tab_map[j][i])
	{
		if (e->map.tab_map[j][i] != '1')
		{
			printf("Error map\nOnly '1' on the edges of your map");
			ft_exit(e);
		}
		j++;
	}
}

void	ft_check_wall(t_env *e)
{
	int	i;
	
	i = 0;
	while (e->map.tab_map[0][i])
	{	
		if (e->map.tab_map[0][i] != '1')
		{
			printf("Error map\nOnly '1' on the edges of your map");
			ft_exit(e);
		}
		i++;
	}
	i = 0;
	while (e->map.tab_map[i][0])
	{
		
		if (e->map.tab_map[i][0] != '1')
		{
			printf("Error map\nOnly '1' on the edges of your map");
			ft_exit(e);
		}
		i++;
	}
	ft_check_wall_next(e);
}

void	ft_check_resolution(t_env *e)
{
	if (e->axes.axe_x > 2560)
		e->axes.axe_x = 2560;
	if (e->axes.axe_y > 1440)
		e->axes.axe_y = 1440;
}
