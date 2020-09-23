/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:46:14 by flavon            #+#    #+#             */
/*   Updated: 2020/09/21 14:44:42 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_paint(t_paint *paint)
{
	paint->wall_x = 0;
	paint->step = 0;
	paint->tex_pos = 0;
	paint->tex_x = 0;
	paint->tex_y = 0;
	paint->tex_h = 0;
	paint->tex_w = 0;
}

static void	init_sp_ray(t_ray_sp *ray)
{
	ray->sprite_x = 0;
	ray->sprite_y = 0;
	ray->invdet = 0;
	ray->transform_x = 0;
	ray->transform_y = 0;
	ray->sprite_screen_x = 0;
	ray->sprite_h = 0;
	ray->draw_start_y = 0;
	ray->draw_end_y = 0;
	ray->sprite_w = 0;
	ray->draw_start_x = 0;
	ray->draw_end_x = 0;
	ray->tex_x = 0;
	ray->tex_y = 0;
	ray->sprite = 0;
}

static void	init_ray(t_raycast *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->r_d_x = 0;
	ray->r_d_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	ray->dist_x = 0;
	ray->dist_y = 0;
	ray->dlt_d_x = 0;
	ray->dlt_d_y = 0;
	ray->player_x = 0;
	ray->player_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->wall_start = 0;
	ray->wall_height = 0;
	ray->wall_end = 0;
	ray->wall_side = 0;
	ray->wall_dist = 0;
	ray->buffer = NULL;
}

static void	init_img(t_win *win)
{
	win->mlx = NULL;
	win->win = NULL;
	win->img = NULL;
	win->addr = NULL;
	win->bit_pix = 0;
	win->length = 0;
	win->endian = 0;
	win->width = 0;
	win->height = 0;
}

void			ft_init(t_data *img)
{
	img->sprite_count = 0;
	img->map.map = NULL;
	img->map.line = NULL;
	img->sprite = NULL;
	init_param(&img->par);
	init_keys(&img->key);
	init_paint(&img->paint);
	init_sp_ray(&img->sp_ray);
	init_ray(&img->ray);
	init_img(&img->win);
	init_img(&img->tex.ea_tex);
	init_img(&img->tex.no_tex);
	init_img(&img->tex.we_tex);
	init_img(&img->tex.so_tex);
	init_img(&img->tex.s_tex);
}