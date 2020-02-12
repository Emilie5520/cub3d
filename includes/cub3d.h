/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:52:18 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/12 17:52:26 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <math.h>

typedef struct		s_identifiants
{
	int	R;
	int	NO;
	int	SO;
	int	WE;
	int	EA;
	int	S; 
	int	F; 
	int	C;
}      			t_identifiants;

typedef struct		s_axes
{
	int	axe_x;
	int	axe_y;
}			t_axes;

typedef struct		s_root_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*sprite;
}      			t_root_textures;

typedef struct		s_colors
{
	int	color_sol;
	int	color_plafond;
	int	color_west;
	int	color_east;
	int	color_south;
	int	color_north;
	int	wall;
}      			t_colors;

typedef struct 		s_map
{
	char	**tab_map;
	double	plan_x;
	double	plan_y;
	char	*buff;
	double	pos_n_x;
	double	pos_n_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int	hauteur_line;
	int	draw_start;
	int	draw_end;
}      			t_map;

typedef struct		s_orientation
{
	double 	dir_x;
	double	dir_y;
	char	orientation_perso;
}      			t_orientation;

typedef struct 		s_raycasting
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	double	perp_wall_dist;
	int	step_x;
	int	step_y;
	int	side;
}      			t_raycasting;

typedef struct		s_mlx
{
	void	*ptr;
	void	*win_ptr;
	void	*new_image;
	int    	*get_data;
	int    	bits_per_pixel;
	int 	size_line;
	int 	endian;
	void	*file_to_image;
}	 		t_mlx;

typedef struct		s_mvt
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	rot_right;
	int	rot_left;
	double	old_dir_x;
	double	old_plan_x;
	double	vit_rot;
}		      	t_mvt;

typedef struct 		s_textures
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*win_ptr;
	int		*get_data;
	int 	w;
	int 	h;
}		      	t_textures;

typedef struct		s_t_env
{
	t_identifiants	identifiants;
	t_axes		axes;
	t_root_textures root_textures;
	t_colors	colors;
	t_map		map;
	t_orientation	orientation;
	t_mlx		mlx;
	t_raycasting	raycasting;
	int 			key;
	t_mvt		mvt;
	t_textures 		texture_north;
	t_textures 		texture_south;
	t_textures 		texture_east;
	t_textures 		texture_west;
}			t_env;

void	ft_initialize_parsing(t_env *t_env);
void	ft_parsing_line(t_env *t_env, char *line);
int		ft_read_map(char **argv, t_env *t_env);
int		main(int argc, char **argv);
void	ft_recup_axes(t_env *t_env, char *line);
char	*ft_recup_root(char *line);
int		ft_recup_color(char *line);
void	ft_recup_map(char *line, t_env *t_env);
void	ft_open_window(t_env *t_env);
void	ft_recup_map_2(t_env *t_env);
void	ft_pos_perso(t_env *t_env);
void	ft_orientation_perso(t_env *t_env);
int		ft_is_orientation(t_env *t_env, int i, int j);
void	ft_raycasting(t_env *t_env);
int 	ft_deplacement(t_env *e);
int	ft_key_up(int keycode, t_env *e);
int	ft_key_down(int keycode, t_env *e);
void	ft_init_image(t_env *e);
void	ft_no_wall(int hit, t_env *e);
void	ft_colonne(t_env *e, int x);
void	ft_color_wall(t_env *e);
void	ft_textures(t_env *e);
void	ft_put_textures(t_env *e, int x);

#endif
