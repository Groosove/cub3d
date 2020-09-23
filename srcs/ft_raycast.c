/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 15:22:51 by flavon            #+#    #+#             */
/*   Updated: 2020/09/23 12:58:35 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_wall_side(t_data *img)
{
	if (img->ray.wall_side == 0)
	{
		img->paint.tex_h = img->tex.so_tex.height;
		img->paint.tex_w = img->tex.so_tex.width;
	}
	else if (img->ray.wall_side == 1)
	{
		img->paint.tex_h = img->tex.no_tex.height;
		img->paint.tex_w = img->tex.no_tex.width;
	}
	else if (img->ray.wall_side == 2)
	{
		img->paint.tex_h = img->tex.ea_tex.height;
		img->paint.tex_w = img->tex.ea_tex.width;
	}
	else if (img->ray.wall_side == 3)
	{
		img->paint.tex_h = img->tex.we_tex.height;
		img->paint.tex_w = img->tex.we_tex.width;
	}
}

void	calc_begin_end(t_data *img)
{
	check_wall_side(img);
	img->ray.wall_height = (int)(img->win.height / img->ray.wall_dist);
	img->ray.wall_start = img->win.height / 2 - img->ray.wall_height / 2;
	if (img->ray.wall_start < 0)
		img->ray.wall_start = 0;
	img->ray.wall_end = img->ray.wall_height / 2 + img->win.height / 2;
	if (img->ray.wall_end >= img->win.height)
		img->ray.wall_end = img->win.height - 1;
	if (img->ray.wall_side == 2 || img->ray.wall_side == 3)
		img->paint.wall_x = img->ray.player_y + img->ray.wall_dist
		* img->ray.r_d_y;
	else
		img->paint.wall_x = img->ray.player_x + img->ray.wall_dist
		* img->ray.r_d_x;
	img->paint.wall_x -= floor(img->paint.wall_x);
	img->paint.tex_x = (int)(img->paint.wall_x * (double)(img->paint.tex_w));
	if (img->ray.wall_side == 2 || img->ray.wall_side == 1)
		img->paint.tex_x = img->paint.tex_w - img->paint.tex_x - 1;
	img->paint.step = 1.0 * img->paint.tex_h / img->ray.wall_height;
	img->paint.tex_pos = (img->ray.wall_start - img->win.height / 2
		+ img->ray.wall_height / 2) * img->paint.step;
}

void	ft_calc_wall(t_data *img)
{
	img->ray.hit = 0;
	while (img->ray.hit == 0)
	{
		if (img->ray.dist_x < img->ray.dist_y)
		{
			img->ray.dist_x += img->ray.dlt_d_x;
			img->ray.map_x += img->ray.step_x;
			img->ray.wall_side = (img->ray.r_d_x < 0) ? 2 : 3;
		}
		else
		{
			img->ray.dist_y += img->ray.dlt_d_y;
			img->ray.map_y += img->ray.step_y;
			img->ray.wall_side = (img->ray.r_d_y < 0) ? 0 : 1;
		}
		if (img->map.map[img->ray.map_x][img->ray.map_y] == '1')
			img->ray.hit = 1;
	}
	if (img->ray.wall_side > 1)
		img->ray.wall_dist = ((img->ray.map_x - img->ray.player_x +
			(1 - img->ray.step_x) / 2) / img->ray.r_d_x);
	else
		img->ray.wall_dist = ((img->ray.map_y - img->ray.player_y +
			(1 - img->ray.step_y) / 2) / img->ray.r_d_y);
}

void	calc_player(t_data *img)
{
	if (img->par.dir == 'N')
	{
		img->ray.dir_y = -1;
		img->ray.plane_x = tan(M_PI * FOV / 360);
	}
	else if (img->par.dir == 'W')
	{
		img->ray.dir_x = -1;
		img->ray.plane_y = -tan(M_PI * FOV / 360);
	}
	else if (img->par.dir == 'E')
	{
		img->ray.dir_x = 1;
		img->ray.plane_y = tan(M_PI * FOV / 360);
	}
	else if (img->par.dir == 'S')
	{
		img->ray.dir_y = 1;
		img->ray.plane_x = -tan(M_PI * FOV / 360);
	}
}

void	ft_raycast(t_data *img)
{
	int		x;

	x = 0;
	while (x < img->win.width)
	{
		img->ray.camera_x = 2 * x / (double)img->win.width - 1;
		img->ray.r_d_x = img->ray.dir_x + img->ray.plane_x * img->ray.camera_x;
		img->ray.r_d_y = img->ray.dir_y + img->ray.plane_y * img->ray.camera_x;
		img->ray.map_x = (int)img->ray.player_x;
		img->ray.map_y = (int)img->ray.player_y;
		if (!img->ray.r_d_y)
			img->ray.dlt_d_x = 0;
		else
			img->ray.dlt_d_x = (!img->ray.r_d_x) ? 1 : fabs(1 / img->ray.r_d_x);
		if (!img->ray.r_d_x)
			img->ray.dlt_d_y = 0;
		else
			img->ray.dlt_d_y = (!img->ray.r_d_y) ? 1 : fabs(1 / img->ray.r_d_y);
		ft_calc_step(&img->ray);
		ft_calc_wall(img);
		calc_begin_end(img);
		ft_print_wall(img, x);
		img->ray.buffer[x++] = img->ray.wall_dist;
	}
	ft_get_sprite(img);
}
