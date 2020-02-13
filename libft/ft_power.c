/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouvier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:49:24 by edouvier          #+#    #+#             */
/*   Updated: 2020/02/13 16:59:08 by edouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

float		ft_power(float nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_power(nb, power - 1));
}
