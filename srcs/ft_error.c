/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 08:31:51 by flavon            #+#    #+#             */
/*   Updated: 2020/10/16 16:45:36 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *dst, t_data *img)
{
	ft_puterror("Error\n");
	ft_puterror(dst);
	ft_putchar('\n');
	ft_free(img);
	exit(-1);
}

int		ft_exit(t_data *img)
{
	ft_free(img);
	exit(0);
	return (1);
}

void	ft_check_space(t_data *img)
{
	int i;

	i = 0;
	while (img->map.map[i])
	{
		if (ft_strlen(img->map.map[i]) != 0)
			break ;
		i++;
	}
	while (i < img->map.x - 1)
	{
		if (ft_strlen(img->map.map[i]) == 0)
			error_msg("Invalid map", img);
		i++;
	}
}
