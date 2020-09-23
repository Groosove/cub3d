/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:50:34 by flavon            #+#    #+#             */
/*   Updated: 2020/09/23 11:52:35 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	way_down(t_raycast *ray, t_map *map)
{
	if (check_map_step(map->map, (int)ray->player_x,
					(int)(ray->player_y - ray->dir_y * 0.21)))
		ray->player_y -= ray->dir_y * 0.2;
	if (check_map_step(map->map, (int)(ray->player_x - ray->dir_x * 0.21),
					(int)ray->player_y))
		ray->player_x -= ray->dir_x * 0.2;
}

void	way_up(t_raycast *ray, t_map *map)
{
	if (check_map_step(map->map, (int)ray->player_x,
					(int)(ray->player_y + ray->dir_y * 0.21)))
		ray->player_y += ray->dir_y * 0.2;
	if (check_map_step(map->map, (int)(ray->player_x + ray->dir_x * 0.21),
					(int)ray->player_y))
		ray->player_x += ray->dir_x * 0.2;
}

void	way_left(t_raycast *ray, t_map *map)
{
	if (check_map_step(map->map, (int)ray->player_x,
					(int)(ray->player_y - ray->plane_y * 0.21)))
		ray->player_y -= ray->plane_y * 0.2;
	if (check_map_step(map->map, (int)(ray->player_x - ray->plane_x * 0.21),
					(int)ray->player_y))
		ray->player_x -= ray->plane_x * 0.2;
}

void	way_right(t_raycast *ray, t_map *map)
{
	if (check_map_step(map->map, (int)ray->player_x,
					(int)(ray->player_y + ray->plane_y * 0.21)))
		ray->player_y += ray->plane_y * 0.2;
	if (check_map_step(map->map, (int)(ray->player_x + ray->plane_x * 0.21),
					(int)ray->player_y))
		ray->player_x += ray->plane_x * 0.2;
}

void	ft_rotate(t_raycast *ray, double cosinus)
{
	double	tmp_dir_x;
	double	tmp_plane_x;

	tmp_dir_x = ray->dir_x;
	tmp_plane_x = ray->plane_x;
	ray->dir_x = ray->dir_x * cos(cosinus) - ray->dir_y * sin(cosinus);
	ray->dir_y = tmp_dir_x * sin(cosinus) + ray->dir_y * cos(cosinus);
	ray->plane_x = ray->plane_x * cos(cosinus) - ray->plane_y * sin(cosinus);
	ray->plane_y = tmp_plane_x * sin(cosinus) + ray->plane_y * cos(cosinus);
}
