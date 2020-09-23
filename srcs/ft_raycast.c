/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 15:22:51 by flavon            #+#    #+#             */
/*   Updated: 2020/09/21 14:15:00 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->win.addr + (y * img->win.length + x * (img->win.bit_pix / 8));
	*(unsigned int *)dst = color;
}

void	print_background(t_data *img, int x)
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

void	calc_begin_end(t_data *img)
{
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

void	ft_print_wall(t_data *img, int x)
{
	int color;
	int y;
	y = img->ray.wall_start;
	while (y < img->ray.wall_end)
	{
		img->paint.tex_y = (int)img->paint.tex_pos & (img->paint.tex_h - 1);
		if (img->ray.wall_side == 0)
			color = ft_get_color(&img->tex.so_tex, img->paint.tex_x, img->paint.tex_y);
		else if (img->ray.wall_side == 1)
			color = ft_get_color(&img->tex.no_tex, img->paint.tex_x, img->paint.tex_y);
		else if (img->ray.wall_side == 2)
			color = ft_get_color(&img->tex.ea_tex, img->paint.tex_x, img->paint.tex_y);
		else if (img->ray.wall_side == 3)
			color = ft_get_color(&img->tex.we_tex, img->paint.tex_x, img->paint.tex_y);
		img->paint.tex_pos += img->paint.step;
		ft_pixel_put(img, x, y, color);
		y++;
	}
}

void	ft_calc_step(t_raycast *ray)
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

void	ft_print_sprite(t_data *img)
{
	int		y;
	int		d;
	int		color;

	y = img->sp_ray.draw_start_y;
	while (y < img->sp_ray.draw_end_y)
	{
		d = y * 256 - img->win.height * 128 + img->sp_ray.sprite_h * 128;
		img->sp_ray.tex_y = ((d * img->tex.s_tex.height) / img->sp_ray.sprite_h) / 256;
		color = ft_get_color(&img->tex.s_tex, img->sp_ray.tex_x, img->sp_ray.tex_y);
		if ((color & 0x00FFFFFF) != 0)
			ft_pixel_put(img, img->sp_ray.sprite, y, color);
		y++;
	}
}

void	ft_calc_sprite(t_data *img, t_sprite *sprite)
{
	img->sp_ray.sprite_x = sprite->x - img->ray.player_x;
	img->sp_ray.sprite_y = sprite->y - img->ray.player_y;
	img->sp_ray.invdet = 1.0 / (img->ray.plane_x * img->ray.dir_y - img->ray.dir_x * img->ray.plane_y);
	img->sp_ray.transform_x = img->sp_ray.invdet * (img->ray.dir_y * img->sp_ray.sprite_x - img->ray.dir_x * img->sp_ray.sprite_y);
	img->sp_ray.transform_y = img->sp_ray.invdet * (-img->ray.plane_y * img->sp_ray.sprite_x + img->ray.plane_x * img->sp_ray.sprite_y);
	img->sp_ray.sprite_screen_x = (int)((img->win.width / 2) * (1 + img->sp_ray.transform_x / img->sp_ray.transform_y));
	img->sp_ray.sprite_h = abs((int)((img->win.height / img->sp_ray.transform_y)));
	img->sp_ray.sprite_w = abs((int)((img->win.height / img->sp_ray.transform_y)));
	img->sp_ray.draw_start_y = -img->sp_ray.sprite_h / 2 + img->win.height / 2;
	if (img->sp_ray.draw_start_y < 0)
		img->sp_ray.draw_start_y = 0;
	img->sp_ray.draw_end_y = img->sp_ray.sprite_h / 2 + img->win.height / 2;
	if (img->sp_ray.draw_end_y >= img->win.height) 
		img->sp_ray.draw_end_y = img->win.height - 1;
	img->sp_ray.draw_start_x = -img->sp_ray.sprite_w / 2 + img->sp_ray.sprite_screen_x;
	if (img->sp_ray.draw_start_x < 0)
		img->sp_ray.draw_start_x = 0;
	img->sp_ray.draw_end_x = img->sp_ray.sprite_w / 2 + img->sp_ray.sprite_screen_x;
	if (img->sp_ray.draw_end_x >= img->win.width) 
		img->sp_ray.draw_end_x = img->win.width - 1;
	img->sp_ray.sprite = img->sp_ray.draw_start_x;
	while (img->sp_ray.sprite < img->sp_ray.draw_end_x)
	{
		img->sp_ray.tex_x = (int)(256 * (img->sp_ray.sprite - (-img->sp_ray.sprite_w / 2 + img->sp_ray.sprite_screen_x)) * img->tex.s_tex.width / img->sp_ray.sprite_w) / 256;
		if (img->sp_ray.transform_y > 0 && img->sp_ray.sprite >= 0 && img->sp_ray.sprite < img->win.width && img->sp_ray.transform_y < img->ray.buffer[img->sp_ray.sprite])
			ft_print_sprite(img);
		img->sp_ray.sprite++;
	}
}

void	ft_swap(t_sprite *a, t_sprite *b)
{
	t_sprite tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_get_sprite(t_data *img)
{
	int index;

	index = -1;
	while (++index < img->sprite_count)
		(img->sprite)[index].dist = sqrt(pow(img->ray.player_x - (img->sprite)[index].x, 2) + pow(img->ray.player_y - (img->sprite)[index].y, 2));
	index = 0;
	while (index < img->sprite_count - 1)
	{
		if ((img->sprite)[index].dist < (img->sprite)[index + 1].dist)
		{
			ft_swap(&(img->sprite)[index], &(img->sprite)[index + 1]);
			index = 0;
		}
		index++;
	}
	index = 0;
	while (index < img->sprite_count)
		ft_calc_sprite(img, &img->sprite[index++]);	
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
		img->ray.dlt_d_x = (!img->ray.r_d_y) ? 0 :
							(!img->ray.r_d_x) ? 1 : fabs(1 / img->ray.r_d_x);
		img->ray.dlt_d_y = (!img->ray.r_d_x) ? 0 :
							(!img->ray.r_d_y) ? 1 : fabs(1 / img->ray.r_d_y);
		ft_calc_step(&img->ray);
		ft_calc_wall(img);
		check_wall_side(img);
		calc_begin_end(img);
		print_background(img, x);
		ft_print_wall(img, x);
		img->ray.buffer[x++] = img->ray.wall_dist;
	}
	ft_get_sprite(img);
}
