/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:13:06 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/13 15:38:40 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_delete_space(char *str)
{
	int	i;
	int	j;
	int	k;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			j++;
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * (j + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			tmp[k++] = str[i];
	i++;
	}
	tmp[k] = '\0';
	free(str);
	return (tmp);
}

void	ft_recup_map(char *line, t_env *e)
{
	e->raycasting.y++;
	if (!e->map.buff)
		e->map.buff = ft_strdup("");
	else 
		e->map.buff = ft_strjoin(e->map.buff, "\n", 1);
	e->map.buff = ft_strjoin(e->map.buff, line, 1);
}

void	ft_recup_map_2(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	e->map.buff = ft_delete_space(e->map.buff);
	e->map.tab_map = ft_split(e->map.buff, '\n');
	while (e->map.tab_map[0][i] == '1')
	{
		e->raycasting.x = i++;
	}
}

void	ft_pos_perso(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->map.tab_map[i] && i <= e->raycasting.y)
	{
		while (e->map.tab_map[i][j])
		{
			if (e->map.tab_map[i][j] != '1' && e->map.tab_map[i][j] != '0' &&
					e->map.tab_map[i][j] != '2' && (ft_is_orientation(e, i, j) == 0))
				printf("%s\n", "ERROR");
			if (e->map.tab_map[i][j] == '2')
			{
				e->map.nbr_sprite += 1;
				//e->map.sprite_x = j; 
				//e->map.sprite_y = i;
				//printf("pos 2 x%d\n", e->map.sprite_x);
				//printf("pos 2 y%d\n", e->map.sprite_y);
			}
			if ((ft_is_orientation(e, i, j) == 1))
			{
				e->map.pos_n_x = j + 0.5;
				e->map.pos_n_y = i + 0.5;
			}
			j++;
		}
	i++;
	j = 0;
	}
}
