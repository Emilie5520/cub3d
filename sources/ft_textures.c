/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:49:19 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/10 14:50:18 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

t_textures		ft_info_texture(char *root_texture, t_env *e)
{
	t_textures	texture;

	ft_memset(&texture, 0, sizeof(t_textures));


	texture.win_ptr = mlx_xpm_file_to_image(e->mlx.win_ptr, root_texture, &texture.w, &texture.h);
	texture.get_data = (int *)mlx_get_data_addr(texture.win_ptr, &texture.bits_per_pixel, &texture.size_line, &texture.endian);
	return (texture);
}

void	ft_textures(t_env *e)
{
	e->texture_north = ft_info_texture(e->root_textures.north, e);
	e->texture_south = ft_info_texture(e->root_textures.south, e);
	e->texture_east = ft_info_texture(e->root_textures.east, e);
	e->texture_west = ft_info_texture(e->root_textures.west, e);

}

t_textures	ft_texture_wall(t_env *e)
{
	if (e->raycasting.side == 0 && e->map.ray_dir_x > 0) 
		return (e->texture_north);
	else if (e->raycasting.side == 0 && e->map.ray_dir_x < 0) 
		return (e->texture_south);
	else if (e->raycasting.side == 1 && e->map.ray_dir_y > 0)
		return (e->texture_east);
	else
		return (e->texture_west);
}

void	ft_put_textures(t_env *e, int x)
{
	double	wall_x;
	int 	tex_x;
	int 	tex_y;
	int 	y;
	t_textures 	texture_wall;
	
	printf("pos_x %f\n", e->map.pos_n_x);
	printf("pos_y %f\n", e->map.pos_n_y);
	printf("texture %d\n", texture_wall.w);
	texture_wall = ft_texture_wall(e);
	if (e->raycasting.side == 0)
		wall_x = e->map.pos_n_y + e->raycasting.perp_wall_dist * e->map.ray_dir_y;
	else 
		wall_x = e->map.pos_n_x + e->raycasting.perp_wall_dist * e->map.ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = wall_x * (double)texture_wall.w;
	printf("tex x %d\n", tex_x);
	y = e->map.draw_start;
	while (y < e->map.draw_end)
	{
		tex_y = (y - e->axes.axe_y / 2 + e->map.hauteur_line / 2) * texture_wall.h / e->map.hauteur_line;
		e->mlx.get_data[x + y * (e->mlx.size_line / 4)] = texture_wall.get_data[tex_x + tex_y * texture_wall.w];
		y++;
	}
}