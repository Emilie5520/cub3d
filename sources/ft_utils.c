/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 10:54:08 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/24 14:22:11 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_recup_root(char *line, t_env *e)
{
	int		i;
	char	**tab;
	char	*line2;

	i = 0;
	tab = ft_split(line, ' ');
	line2 = ft_strdup(tab[1]);
	if (tab[2])
	{
		printf("Error\nWrong .cub");
		ft_exit(e);
	}
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab);
	return (line2);
}

int		ft_recup_color(char *line, t_env *e)
{
	int		i;
	int		color;

	i = 1;
	ft_space(line, &i);
	ft_check_color(e, line, i);
	while (line[i] == ' ')
		i++;
	color = ft_atoi(&line[i]) * 65536;
	while (ft_isdigit(line[i]))
		i++;
	color += ft_atoi(&line[++i]) * 256;
	while (ft_isdigit(line[i]))
		i++;
	color += ft_atoi(&line[++i]);
	ft_space(line, &i);
	while (ft_isdigit(line[i]))
		i++;
	ft_space(line, &i);
	if (line[i])
	{
		printf("Error\nWrong .cub");
		ft_exit(e);
	}
	return (color);
}

void	ft_recup_axes(t_env *e, char *line)
{
	int		i;

	i = 0;
	while (ft_isprint(line[i]) == 0)
		i++;
	i++;
	e->axes.axe_x = ft_atoi(&line[i]);
	while (ft_atoi(&line[i]))
		i++;
	while (ft_isprint(line[i]) == 0)
		i++;
	i++;
	e->axes.axe_y = ft_atoi(&line[i]);
	ft_space(line, &i);
	while (ft_isdigit(line[i]))
		i++;
	ft_space(line, &i);
	if (line[i])
	{
		printf("Error\nWrong .cub");
		ft_exit(e);
	}
}

int		ft_key_down(int keycode, t_env *e)
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

int		ft_key_up(int keycode, t_env *e)
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
		ft_exit(e);
	return (0);
}
