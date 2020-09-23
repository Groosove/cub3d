/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:18:30 by flavon            #+#    #+#             */
/*   Updated: 2020/09/23 12:58:07 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_calc_step(t_raycast *ray)
{
	if (ray->r_d_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = (ray->player_x - ray->map_x) * ray->dlt_d_x;
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = (1.0 + ray->map_x - ray->player_x) * ray->dlt_d_x;
	}
	if (ray->r_d_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (ray->player_y - ray->map_y) * ray->dlt_d_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = (1.0 + ray->map_y - ray->player_y) * ray->dlt_d_y;
	}
}

int			ft_get_color(t_win *img, int x, int y)
{
	int		color;

	color = 0;
	if (!img->width || !img->height)
		return (0);
	x = abs(x);
	y = abs(y);
	if ((x > img->width || y > img->height || x < 0 || y < 0))
		return (0);
	color = *(int *)(img->addr + ((x + (y * img->width))
		* (img->bit_pix / 8)));
	return (color);
}

void		ft_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->win.addr + (y * img->win.length + x * (img->win.bit_pix / 8));
	*(unsigned int *)dst = color;
}

void		print_background(t_data *img, int x)
{
	int y;

	y = 0;
	while (y < img->ray.wall_start)
	{
		ft_pixel_put(img, x, y, img->par.c_col);
		y++;
	}
	y = img->ray.wall_end;
	while (y < img->win.height)
	{
		ft_pixel_put(img, x, y, img->par.f_col);
		y++;
	}
}

void		ft_print_wall(t_data *img, int x)
{
	int color;
	int y;

	print_background(img, x);
	y = img->ray.wall_start;
	while (y < img->ray.wall_end)
	{
		img->paint.tex_y = (int)img->paint.tex_pos & (img->paint.tex_h - 1);
		if (img->ray.wall_side == 0)
			color =
			ft_get_color(&img->tex.so_tex, img->paint.tex_x, img->paint.tex_y);
		else if (img->ray.wall_side == 1)
			color =
			ft_get_color(&img->tex.no_tex, img->paint.tex_x, img->paint.tex_y);
		else if (img->ray.wall_side == 2)
			color =
			ft_get_color(&img->tex.ea_tex, img->paint.tex_x, img->paint.tex_y);
		else if (img->ray.wall_side == 3)
			color =
			ft_get_color(&img->tex.we_tex, img->paint.tex_x, img->paint.tex_y);
		img->paint.tex_pos += img->paint.step;
		ft_pixel_put(img, x, y, color);
		y++;
	}
}
