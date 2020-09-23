/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:58:57 by flavon            #+#    #+#             */
/*   Updated: 2020/09/23 11:44:04 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				check_map_step(char **map, int x, int y)
{
	if (map[x][y] == ' ' || map[x][y] == '0' || map[x][y] == 'N'
	|| map[x][y] == 'S' || map[x][y] == 'W' || map[x][y] == 'E')
		return (1);
	return (0);
}

int				ft_key_code(int key, t_data *img)
{
	if (key == 53)
		ft_exit();
	else if (key == UP)
		img->key.up = 1;
	else if (key == DOWN)
		img->key.down = 1;
	else if (key == LEFT)
		img->key.left = 1;
	else if (key == RIGHT)
		img->key.right = 1;
	else if (key == R_RIGHT)
		img->key.r_right = 1;
	else if (key == R_LEFT)
		img->key.r_left = 1;
	return (0);
}

int				ft_key_release(int key, t_data *img)
{
	if (key == UP)
		img->key.up = 0;
	if (key == DOWN)
		img->key.down = 0;
	if (key == LEFT)
		img->key.left = 0;
	if (key == RIGHT)
		img->key.right = 0;
	if (key == R_LEFT)
		img->key.r_left = 0;
	if (key == R_RIGHT)
		img->key.r_right = 0;
	return (0);
}

int				ft_run(t_data *img)
{
	if (img->key.up)
		way_up(&img->ray, &img->map);
	if (img->key.down)
		way_down(&img->ray, &img->map);
	if (img->key.left)
		way_left(&img->ray, &img->map);
	if (img->key.right)
		way_right(&img->ray, &img->map);
	if (img->key.r_left)
		ft_rotate(&img->ray, -0.05);
	if (img->key.r_right)
		ft_rotate(&img->ray, 0.05);
	if (!(img->win.img = mlx_new_image(img->win.mlx,
									img->win.width, img->win.height)))
		error_msg("Image error");
	if (!(img->win.addr = mlx_get_data_addr(img->win.img,
						&img->win.bit_pix, &img->win.length, &img->win.endian)))
		error_msg("Image error");
	ft_raycast(img);
	mlx_put_image_to_window(img->win.mlx, img->win.win, img->win.img, 0, 0);
	return (0);
}
