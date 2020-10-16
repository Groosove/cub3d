/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:58:24 by flavon            #+#    #+#             */
/*   Updated: 2020/10/16 13:29:56 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		validate_input_argc(char **argv, int argc, t_data *img)
{
	int ltg;

	if (argc == 1)
		error_msg("No map in arguments", img);
	if (argc == 2)
	{
		ltg = ft_strlen(argv[1]);
		if (argv[1][ltg - 4] != '.' || argv[1][ltg - 3] != 'c' ||
			argv[1][ltg - 2] != 'u' || argv[1][ltg - 1] != 'b')
			error_msg("Filename is not .cub", img);
	}
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 6) != 0)
			error_msg("Error flag screenshot", img);
	if (argc == 4)
		error_msg("Error arguments", img);
}

void		ft_mlx_init(t_data *img)
{
	img->win.mlx = mlx_init();
	if (!(img->win.win = mlx_new_window(img->win.mlx, img->win.width,
		img->win.height, "cub3D")))
		error_msg("MLX Failed", img);
	if (!(img->win.img = mlx_new_image(img->win.mlx,
		img->win.width, img->win.height)))
		error_msg("MLX Failed", img);
	if (!(img->win.addr = mlx_get_data_addr(img->win.img,
		&img->win.bit_pix, &img->win.length, &img->win.endian)))
		error_msg("MLX Failed", img);
	img->ray.buffer = (double *)malloc(sizeof(double) * (img->win.width + 1));
}

void		create_window(t_data *img)
{
	int count;
	int x;
	int y;

	count = 1;
	while (ft_isspace(img->map.line[count]))
		count++;
	img->win.width = ft_atoi(img->map.line, &count);
	while (ft_isspace(img->map.line[count]))
		count++;
	img->win.height = ft_atoi(img->map.line, &count);
	if (img->map.line[count] != '\0')
		error_msg("Character after arguments", img);
	mlx_get_screen_size(img->win.mlx, &x, &y);
	img->win.width = (img->win.width > x || img->win.width <= 0) ?
												x : img->win.width;
	img->win.height = (img->win.height > y || img->win.height <= 0) ?
												y : img->win.height;
}

void		ft_get_param(char *src, t_data *img)
{
	int count;
	int ltg;

	count = 2;
	while (src[count] != 0 && ft_isspace(src[count]) == 1)
		count++;
	if (src[0] == 'N' && src[1] == 'O' && img->par.no_img == 0)
		img->par.no_img = ft_strdup(&src[count]);
	else if (src[0] == 'S' && src[1] == 'O' && img->par.so_img == 0)
		img->par.so_img = ft_strdup(&src[count]);
	else if (src[0] == 'W' && src[1] == 'E' && img->par.we_img == 0)
		img->par.we_img = ft_strdup(&src[count]);
	else if (src[0] == 'E' && src[1] == 'A' && img->par.ea_img == 0)
		img->par.ea_img = ft_strdup(&src[count]);
	else if (src[0] == 'S' && img->par.s_img == 0)
		img->par.s_img = ft_strdup(&src[count]);
	else
		error_msg("Second parametr", img);
	ltg = ft_strlen(src);
	if (src[ltg] != '\0')
		error_msg("Character after arguments", img);
	if (src[ltg - 4] != '.' || src[ltg - 3] != 'x'
		|| src[ltg - 2] != 'p' || src[ltg - 1] != 'm')
		error_msg("Filename is not xpm", img);
}

int			sprite_init(t_data *img, int x, int y)
{
	t_sprite	*list_elem;
	int			count;

	count = 0;
	if ((list_elem =
		(t_sprite*)malloc(sizeof(t_sprite) * (img->sprite_count + 1))) == NULL)
		return (0);
	if (img->sprite_count != 0)
	{
		while (count < img->sprite_count)
		{
			((t_sprite *)list_elem)[count] = img->sprite[count];
			count++;
		}
		free(img->sprite);
	}
	img->sprite = list_elem;
	img->sprite[count].x = (double)x + 0.5;
	img->sprite[count].y = (double)y + 0.5;
	img->sprite[count].index = img->sprite_count;
	img->sprite_count++;
	return (1);
}
