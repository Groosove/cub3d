/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 12:18:46 by flavon            #+#    #+#             */
/*   Updated: 2020/09/23 12:38:54 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_print_sprite(t_data *img)
{
	int		y;
	int		d;
	int		color;

	y = img->sp_ray.draw_start_y;
	while (y < img->sp_ray.draw_end_y)
	{
		d = y * 256 - img->win.height * 128 + img->sp_ray.sprite_h * 128;
		img->sp_ray.tex_y =
		((d * img->tex.s_tex.height) / img->sp_ray.sprite_h) / 256;
		color =
		ft_get_color(&img->tex.s_tex, img->sp_ray.tex_x, img->sp_ray.tex_y);
		if ((color & 0x00FFFFFF) != 0)
			ft_pixel_put(img, img->sp_ray.sprite, y, color);
		y++;
	}
}

static void	ft_calc_sprite_utils(t_data *img, t_sprite *sprite)
{
	img->sp_ray.sprite_x = sprite->x - img->ray.player_x;
	img->sp_ray.sprite_y = sprite->y - img->ray.player_y;
	img->sp_ray.invdet = 1.0 / (img->ray.plane_x *
						img->ray.dir_y - img->ray.dir_x * img->ray.plane_y);
	img->sp_ray.transform_x = img->sp_ray.invdet * (img->ray.dir_y *
				img->sp_ray.sprite_x - img->ray.dir_x * img->sp_ray.sprite_y);
	img->sp_ray.transform_y = img->sp_ray.invdet * (-img->ray.plane_y *
				img->sp_ray.sprite_x + img->ray.plane_x * img->sp_ray.sprite_y);
	img->sp_ray.sprite_screen_x = (int)((img->win.width / 2) *
				(1 + img->sp_ray.transform_x / img->sp_ray.transform_y));
	img->sp_ray.sprite_h =
		abs((int)((img->win.height / img->sp_ray.transform_y)));
	img->sp_ray.sprite_w =
		abs((int)((img->win.height / img->sp_ray.transform_y)));
	img->sp_ray.draw_start_y = -img->sp_ray.sprite_h / 2 + img->win.height / 2;
}

static void	ft_calc_sprite(t_data *img)
{
	if (img->sp_ray.draw_start_y < 0)
		img->sp_ray.draw_start_y = 0;
	img->sp_ray.draw_end_y = img->sp_ray.sprite_h / 2 + img->win.height / 2;
	if (img->sp_ray.draw_end_y >= img->win.height)
		img->sp_ray.draw_end_y = img->win.height - 1;
	img->sp_ray.draw_start_x =
		-img->sp_ray.sprite_w / 2 + img->sp_ray.sprite_screen_x;
	if (img->sp_ray.draw_start_x < 0)
		img->sp_ray.draw_start_x = 0;
	img->sp_ray.draw_end_x =
		img->sp_ray.sprite_w / 2 + img->sp_ray.sprite_screen_x;
	if (img->sp_ray.draw_end_x >= img->win.width)
		img->sp_ray.draw_end_x = img->win.width - 1;
	img->sp_ray.sprite = img->sp_ray.draw_start_x;
	while (img->sp_ray.sprite < img->sp_ray.draw_end_x)
	{
		img->sp_ray.tex_x = (int)(256 * (img->sp_ray.sprite -
			(-img->sp_ray.sprite_w / 2 + img->sp_ray.sprite_screen_x)) *
				img->tex.s_tex.width / img->sp_ray.sprite_w) / 256;
		if (img->sp_ray.transform_y > 0 && img->sp_ray.sprite >= 0 &&
			img->sp_ray.sprite < img->win.width &&
			img->sp_ray.transform_y < img->ray.buffer[img->sp_ray.sprite])
			ft_print_sprite(img);
		img->sp_ray.sprite++;
	}
}

void		ft_get_sprite(t_data *img)
{
	int			index;
	t_sprite	tmp;

	index = -1;
	while (++index < img->sprite_count)
		(img->sprite)[index].dist =
			sqrt(pow(img->ray.player_x - (img->sprite)[index].x, 2) +
				pow(img->ray.player_y - (img->sprite)[index].y, 2));
	index = -1;
	while (++index < img->sprite_count - 1)
		if ((img->sprite)[index].dist < (img->sprite)[index + 1].dist)
		{
			tmp = (img->sprite)[index];
			(img->sprite)[index] = (img->sprite)[index + 1];
			(img->sprite)[index + 1] = tmp;
			index = 0;
		}
	index = 0;
	while (index < img->sprite_count)
	{
		ft_calc_sprite_utils(img, &img->sprite[index]);
		ft_calc_sprite(img);
		index++;
	}
}
