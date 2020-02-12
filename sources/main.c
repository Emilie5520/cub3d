/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:37:21 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/12 17:57:25 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	main(int argc, char **argv)
{

	t_env e;

	(void)argc;
	
	ft_initialize_parsing(&e);
	ft_read_map(argv, &e);
	ft_open_window(&e);
}
