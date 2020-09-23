/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:50:34 by flavon            #+#    #+#             */
/*   Updated: 2020/09/21 14:16:40 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	way_down(t_data *img)
{
	if (check_map_step(img->map.map, (int)img->ray.player_x, (int)(img->ray.player_y - img->ray.dir_y * 0.21)))
			img->ray.player_y -= img->ray.dir_y * 0.2;
	if (check_map_step(img->map.map, (int)(img->ray.player_x - img->ray.dir_x * 0.21), (int)img->ray.player_y))
			img->ray.player_x -= img->ray.dir_x * 0.2;
}

void	way_up(t_data *img)
{
	if (check_map_step(img->map.map, (int)img->ray.player_x, (int)(img->ray.player_y + img->ray.dir_y * 0.21)))
			img->ray.player_y += img->ray.dir_y * 0.2;
	if (check_map_step(img->map.map, (int)(img->ray.player_x + img->ray.dir_x * 0.21), (int)img->ray.player_y))
			img->ray.player_x += img->ray.dir_x * 0.2;
}

void	way_left(t_data *img)
{
	if (check_map_step(img->map.map, (int)img->ray.player_x, (int)(img->ray.player_y - img->ray.plane_y * 0.21)))
			img->ray.player_y -= img->ray.plane_y * 0.2;
	if (check_map_step(img->map.map, (int)(img->ray.player_x - img->ray.plane_x * 0.21), (int)img->ray.player_y))
			img->ray.player_x -= img->ray.plane_x * 0.2;
}

void	way_right(t_data *img)
{
	if (check_map_step(img->map.map, (int)img->ray.player_x, (int)(img->ray.player_y + img->ray.plane_y * 0.21)))
			img->ray.player_y += img->ray.plane_y * 0.2;
	if (check_map_step(img->map.map, (int)(img->ray.player_x + img->ray.plane_x * 0.21), (int)img->ray.player_y))
			img->ray.player_x += img->ray.plane_x * 0.2;
}

void	ft_rotate(t_data *img, double cosinus)
{
	double	tmp_dir_x;
	double	tmp_plane_x;

	tmp_dir_x = img->ray.dir_x;
	tmp_plane_x = img->ray.plane_x;
	img->ray.dir_x = img->ray.dir_x * cos(cosinus) - img->ray.dir_y * sin(cosinus);
	img->ray.dir_y = tmp_dir_x * sin(cosinus) + img->ray.dir_y * cos(cosinus);
	img->ray.plane_x = img->ray.plane_x * cos(cosinus) - img->ray.plane_y * sin(cosinus);
	img->ray.plane_y = tmp_plane_x * sin(cosinus) + img->ray.plane_y * cos(cosinus);
}