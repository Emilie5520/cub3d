/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:40:15 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/10 14:30:22 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_initialize_parsing(t_env *e)
{
	ft_memset(e, 0, sizeof(t_env));
}

void	ft_parsing_line(t_env *e, char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'R')
	{
		e->identifiants.R = 1;
		ft_recup_axes(e, line);
	}
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		e->identifiants.NO = 1;
		e->root_textures.north = ft_recup_root(line);
	}
	if (line[i] == 'S' && line[i + 1] == 'O')
	{
		e->identifiants.SO = 1;
		e->root_textures.south = ft_recup_root(line);
	}
	if (line[i] == 'W' && line[i + 1] == 'E')
	{
		e->identifiants.WE = 1;
		e->root_textures.west = ft_recup_root(line);

	}
	if (line[i] == 'E' && line[i + 1] == 'A')
	{
		e->identifiants.EA = 1;
		e->root_textures.east = ft_recup_root(line);
	}
	if (line[i] == 'S')
	{
		e->identifiants.S = 1;
		e->root_textures.sprite = ft_recup_root(line);
	}
	if (line[i] == 'F')
	{
		e->identifiants.F = 1;
		e->colors.color_sol = ft_recup_color(line);
	}
	if (line[i] == 'C')
	{
		e->identifiants.C = 1;
		e->colors.color_plafond = ft_recup_color(line);
	}
	if (line[i] == '1' || line[i] == '0')
	{
		ft_recup_map(line, e);
	}
}

int	ft_read_map(char **argv, t_env *e)
{
	int	ret;
	int	fd;
	char	*line;

	ret = 1;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ret == -1)
			return (0);
		ft_parsing_line(e, line);
	}
	close(fd);
	ft_recup_map_2(e);
	ft_pos_perso(e);
	ft_orientation_perso(e);
	return (1);
}
