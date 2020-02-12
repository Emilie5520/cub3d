/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:12:54 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/10 14:49:09 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_recup_color(char *line)
{
	int	i;
	int	color;

	i = 0;
	i++;
	while (line[i] == ' ')
		i++;
	color = ft_atoi(&line[i]) * 65536;
	while (ft_isdigit(line[i]))
		i++;
	color += ft_atoi(&line[++i]) * 256;
	while (ft_isdigit(line[i]))
		i++;
	color += ft_atoi(&line[++i]);
	return (color);
}

