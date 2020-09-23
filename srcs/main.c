/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:52:49 by flavon            #+#    #+#             */
/*   Updated: 2020/09/22 22:52:38 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_find_objects(t_data *img)
{
	int x;
	int y;

	x = 0;
	while (img->map.map[x] != 0)
	{
		y = 0;
		while (img->map.map[x][y] != 0)
		{
			if (img->map.map[x][y] == 'E' ||
				img->map.map[x][y] == 'N' ||
				img->map.map[x][y] == 'S' ||
				img->map.map[x][y] == 'W')
				{
					img->ray.player_x = (double)x + 0.5;
					img->ray.player_y = (double)y + 0.5;
					img->par.dir = img->map.map[x][y];
				}
			else if (img->map.map[x][y] == '2')
				if(sprite_init(img, x, y) == 0)
					error_msg("Sprite error");
			y++;
		}
		x++;
	}
}

static t_list	*parse_map_cub(char *filename)
{
	t_list *head;
	t_list *tmp;
	int fd;
	char *line;

	tmp = NULL;
	head = NULL;
	if ((fd = open(filename, O_RDONLY)) <= 0)
		error_msg("Invalid file");
	while (get_next_line(fd, &line) > 0)
	{
		if ((tmp = ft_lstnew(line)) == 0)
			error_msg("Memmory error");
		ft_lstadd_back(&head, tmp);
			
	}
	if ((tmp = ft_lstnew(line)) == 0)
		error_msg("Memmory error");
	ft_lstadd_back(&head, tmp);
	close(fd);
	return (head);
}

static	t_data	parse(t_data img, char *filename)
{
	t_list *head;
	
	head = parse_map_cub(filename);
	while (head != NULL)
	{
		img.map.line = head->content;
		if (img.map.line[0] == 'R')
			create_window(&img);
		else if ((img.map.line[0] == 'N' && img.map.line[1] == 'O') ||
				(img.map.line[0] == 'S' && img.map.line[1] == 'O') ||
				(img.map.line[0] == 'W' && img.map.line[1] == 'E') ||
				(img.map.line[0] == 'E' && img.map.line[1] == 'A') ||
				(img.map.line[0] == 'S'))
					ft_get_param(&img.par, img.map.line);
		else if (img.map.line[0] == 'F')
			img.par.f_col = ft_calc_color(&img.map.line[1]);
		else if (img.map.line[0] == 'C')
			img.par.c_col = ft_calc_color(&img.map.line[1]);
		else
			break;
		head = head->next;
	}
	make_map(&img, &head, ft_lstsize(head));
	return (img);
}

static int		check_arguments(t_data *img)
{
	int count;

	count = 0;
	if (img->win.width != 0 && img->win.height != 0)
		count += 1;
	if (img->par.c_col != 0 || img->par.f_col != 0)
		count += 2;
	if (img->par.ea_img != 0 && img->par.no_img != 0 && img->par.s_img != 0
		&& img->par.so_img != 0 && img->par.we_img != 0)
		count += 5;
	if (count == 8)
		return (1);
	return (0);
}

static int	flood_fill(char **map, int x, int y, int size)
{
	if (map[x][y] == ' ' || x < 0 || y < 0 || map[x][y] == '\0'
		|| x >= size)
		return (0);
	if (map[x][y] == '1' || map[x][y] == '.')
		return (1);
	map[x][y] = '.';
	return (flood_fill(map, x - 1, y, size)
		&& flood_fill(map, x + 1, y, size)
		&& flood_fill(map, x, y - 1, size)
		&& flood_fill(map, x, y + 1, size));
}

static int		validate_map(t_data *img)
{
	int i;
	int j;

	i = 0;
	ft_find_objects(img);
	if (!flood_fill(img->map.map, (int)(img->ray.player_x - 0.5),
		(int)(img->ray.player_y - 0.5), img->map.x + 1))
		error_msg("Invalid map");
	while (img->map.map[i])
	{
		j = -1;
		while (img->map.map[i][++j])
			if (img->map.map[i][j] == '.')
				img->map.map[i][j] = '0';
		i++;
	}
	i = -1;
	while (++i < img->sprite_count)
		img->map.map[(int)(img->sprite[i].x - 0.5)][(int)(img->sprite[i].y - 0.5)] = '2';
	return (1);	
}

int				main(int argc, char **argv)
{
	t_data img;

	ft_init(&img);
	validate_input_argc(argv, argc);
	img = parse(img, argv[1]);
	if (check_arguments(&img) == 1)
		if (!validate_map(&img))
			error_msg("Invalid map");
	ft_mlx_init(&img);
	if (load_textures(&img.tex, &img.win, &img.par) == 0)
		error_msg("Error texture");
	calc_player(&img);
	ft_raycast(&img);
	if (argc == 3)
		ft_screen_shot(&img);
	mlx_put_image_to_window(img.win.mlx, img.win.win, img.win.img, 0, 0);
	mlx_hook(img.win.win, 2, 1L << 0, &ft_key_code, &img);
	mlx_hook(img.win.win, 3, 1L << 1, &ft_key_release, &img);
	mlx_hook(img.win.win, 17, 1L << 17, &ft_exit, &img);
	mlx_loop_hook(img.win.mlx, &ft_run, &img);
	mlx_loop(img.win.mlx);
	return (0);
}