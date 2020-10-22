/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:10:44 by flavon            #+#    #+#             */
/*   Updated: 2020/10/21 19:21:58 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_check_around(t_data *img, int x, int y)
{
	if (y - 1 < 0 || x - 1 < 0)
		error_msg("Invalid map", img);
	if (img->map.map[x][y + 1] == '\0' ||
		img->map.map[x][y + 1] == ' ' || img->map.map[x][y - 1] == '\0')
		error_msg("Invalid map", img);
	if (img->map.map[x + 1][y] == '\0' || img->map.map[x - 1][y] == ' ')
		error_msg("Invalid map", img);
}

static void	ft_find_objects(t_data *img)
{
	int x;
	int y;

	x = -1;
	while (img->map.map[++x] != 0)
	{
		y = -1;
		while (img->map.map[x][++y] != 0)
			if (img->map.map[x][y] == '0')
				ft_check_around(img, x, y);
			else if (ft_strchr("ENSW", img->map.map[x][y]))
			{
				img->ray.player_x = (double)x + 0.5;
				img->ray.player_y = (double)y + 0.5;
				if (img->par.dir == 0)
					img->par.dir = img->map.map[x][y];
				else
					error_msg("Second player on map", img);
			}
			else if (img->map.map[x][y] == '2')
				if (sprite_init(img, x, y) == 0)
					error_msg("Sprite error", img);
	}
	if (img->par.dir == 0)
		error_msg("No player on map", img);
}

static int	flood_fill(char **map, int x, int y, int size)
{
	if (map[x] == NULL)
		return (0);
	if (map[x][y] == ' ' || x < 0 || y < 0 || map[x][y] == '\0' || x > size)
		return (0);
	if (map[x][y] == '1' || map[x][y] == '.')
		return (1);
	map[x][y] = '.';
	return (flood_fill(map, x - 1, y, size)
		&& flood_fill(map, x + 1, y, size)
		&& flood_fill(map, x, y - 1, size)
		&& flood_fill(map, x, y + 1, size));
}

static void	ft_check_map_valid(char **map, t_data *img)
{
	int x;
	int y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
			if (map[x][y] == ' ' || map[x][y] == '0' ||
				map[x][y] == '1' || map[x][y] == '2' ||
				map[x][y] == 'N' || map[x][y] == 'E' ||
				map[x][y] == 'W' || map[x][y] == 'S')
				y++;
			else
				error_msg("Invalid map", img);
		x++;
	}
}

int			validate_map(t_data *img)
{
	int i;
	int j;

	i = -1;
	ft_check_map_valid(img->map.map, img);
	ft_find_objects(img);
	if (!flood_fill(img->map.map, (int)(img->ray.player_x - 0.5),
		(int)(img->ray.player_y - 0.5), img->map.x + 1))
		error_msg("Invalid map", img);
	while (img->map.map[++i])
	{
		j = -1;
		while (img->map.map[i][++j])
			if (img->map.map[i][j] == '.')
				img->map.map[i][j] = '0';
	}
	i = -1;
	while (++i < img->sprite_count)
		img->map.map[(int)(img->sprite[i].x - 0.5)]
					[(int)(img->sprite[i].y - 0.5)] = '2';
	return (1);
}
