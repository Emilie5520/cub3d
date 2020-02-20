/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:08:51 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/20 22:52:43 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_check_wall_next(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	j = e->raycasting.y - 1;
	while (i < e->raycasting.x && e->map.tab_map[j][i])
	{
		if (e->map.tab_map[j][i] != '1')
		{
			printf("Error map\nOnly 13 on the edges of your map");
			ft_exit(e);
		}
		i++;
	}
	j = 1;
	i = e->raycasting.x + 1;
	while (j < e->raycasting.y)
	{
		if (e->map.tab_map[j][i] != '1')
		{
			printf("Error map\nOnly 14 on the edges of your map");
			ft_exit(e);
		}
		j++;
	}
}

void	ft_check_wall(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->raycasting.x && e->map.tab_map[0][i])
	{
		if (e->map.tab_map[0][i] != '1')
		{
			printf("Error map\nOnly 1 on the edges of your map");
			ft_exit(e);
		}
		i++;
	}
	i = 0;
	while (i < e->raycasting.y && e->map.tab_map[i][0])
	{
		if (e->map.tab_map[i][0] != '1')
		{
			printf("Error map\nOnly 1 on the edges of your map");
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
	if (e->axes.axe_x <= 0 || e->axes.axe_y <= 0)
	{
		printf("Error\nResolution <= 0");
		ft_exit(e);
	}
}

void	ft_check_color(t_env *e, char *line, int i)
{
	int	j;

	j = ft_isdigit(line[i]) ? 1 : 0;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		j--;
	while (ft_isdigit(line[i]))
		i++;
	j += line[i] == ',' ? 1 : 0;
	j += ft_isdigit(line[++i]) ? 1 : 0;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		j--;
	while (ft_isdigit(line[i]))
		i++;
	j += line[i] == ',' ? 1 : 0;
	j += ft_isdigit(line[++i]) ? 1 : 0;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		j--;
	while (ft_isdigit(line[i]))
		i++;
	ft_space(line, &i);
	j -= line[i] != '\0' ? 1 : 0;
	if (j != 5)
		printf("Error\nWrong color");
	if (j != 5)
		ft_exit(e);
}
