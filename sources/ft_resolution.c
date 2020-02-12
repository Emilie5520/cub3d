/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 19:30:22 by edouvier          #+#    #+#             */
/*   Updated: 2020/01/29 20:14:18 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_recup_axes(t_env *e, char *line)
{
	int 	i;

	i = 0;
	while (ft_isprint(line[i]) == 0)
		i++;
	i++;;
	e->axes.axe_x = ft_atoi(&line[i]);
	while (ft_atoi(&line[i]))
		i++;
	while (ft_isprint(line[i]) == 0)
		i++;
	i++;
	e->axes.axe_y = ft_atoi(&line[i]);
}