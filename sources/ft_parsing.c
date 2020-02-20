/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:40:15 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/20 22:36:23 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_initialize_parsing(t_env *e)
{
	ft_memset(e, 0, sizeof(t_env));
}
int	ft_check_identifiants(t_env *e)
{
	if (e->identifiants.r != 1 || e->identifiants.no != 1 || e->identifiants.so != 1 || e->identifiants.we != 1 || 
			e->identifiants.ea != 1 || e->identifiants.s != 1 || e->identifiants.f != 1 || e->identifiants.c != 1 || e->identifiants.m != 1)
		return (0);
	else
		return (1);
}

void	ft_parsing_line(t_env *e, char *line)
{
	int	i;

	i = 0;
	ft_space(line, &i);
	if (line[i] == 'R' && e->identifiants.m == 0)
	{
		ft_recup_axes(e, line);
		e->identifiants.r = 1;
	}
	else if (line[i] == 'N' && line[i + 1] == 'O' && e->identifiants.m == 0)
	{
		e->root_textures.north = ft_recup_root(line, e);
		e->identifiants.no = 1;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O' && e->identifiants.m == 0)
	{
		e->root_textures.south = ft_recup_root(line, e);
		e->identifiants.so = 1;
	}
	else if (line[i] == 'W' && line[i + 1] == 'E' && e->identifiants.m == 0)
	{
		e->root_textures.west = ft_recup_root(line, e);
		e->identifiants.we = 1;
	}
	else if (line[i] == 'E' && line[i + 1] == 'A' && e->identifiants.m == 0)
	{
		e->root_textures.east = ft_recup_root(line, e);
		e->identifiants.ea = 1;
	}
	else if (line[i] == 'S' && e->identifiants.m == 0)
	{
		e->root_textures.sprite = ft_recup_root(line, e);
		e->identifiants.s = 1;
	}
	else if (line[i] == 'F' && e->identifiants.m == 0)
	{
		e->colors.color_sol = ft_recup_color(line, e);
		e->identifiants.f = 1;
	}
	else if (line[i] == 'C' && e->identifiants.m == 0)
	{
		e->colors.color_plafond = ft_recup_color(line, e);
		e->identifiants.c = 1;
	}
	else if (line[i] == '1' || line[i] == '0')
	{
		ft_recup_map(line, e);
		e->identifiants.m = 1;
	}
	else if (line && (line[i] != '1' || line[i] != '0') && e->identifiants.m == 1)
	{
		printf("Error\nmap1");
		ft_exit(e);
	}
	printf("line %c\n", line[i]);
}

int		ft_read_map(char **argv, t_env *e)
{
	int		ret;
	int		fd;
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
	if (ft_check_identifiants(e) == 0)
	{
		printf("Error\nmap");
		ft_exit(e);
	}
	ft_recup_map_2(e);
	ft_pos_perso(e);
	ft_orientation_perso(e);
	return (1);
}
