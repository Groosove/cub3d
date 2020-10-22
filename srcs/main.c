/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:52:49 by flavon            #+#    #+#             */
/*   Updated: 2020/10/21 19:27:54 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*parse_map_cub(char *filename, t_data *img)
{
	t_list	*head;
	t_list	*tmp;
	int		fd;
	char	*line;

	tmp = NULL;
	head = NULL;
	if ((fd = open(filename, O_RDONLY)) <= 0)
		error_msg("Invalid file", img);
	while (get_next_line(fd, &line) > 0)
	{
		if (line == 0)
			continue ;
		if (!(tmp = ft_lstnew(line)))
			error_msg("Memmory error", img);
		ft_lstadd_back(&head, tmp);
	}
	if ((tmp = ft_lstnew(line)) == 0)
		error_msg("Memmory error", img);
	ft_lstadd_back(&head, tmp);
	close(fd);
	return (head);
}

static	int		arg_parse(char *line, t_data *img)
{
	if (line[0] == 'R')
		create_window(line, img);
	else if ((line[0] == 'N' && line[1] == 'O') ||
			(line[0] == 'S' && line[1] == 'O') ||
			(line[0] == 'W' && line[1] == 'E') ||
			(line[0] == 'E' && line[1] == 'A') ||
			(line[0] == 'S'))
		ft_get_param(line, img);
	else if (line[0] == 'F')
		img->par.f_col = ft_calc_color(&line[1], &img->par.f, img);
	else if (line[0] == 'C')
		img->par.c_col = ft_calc_color(&line[1], &img->par.c, img);
	else if (line[0] == '1' ||
			line[0] == ' ' || line[0] == '0' || line[0] == '2')
		return (0);
	else if (ft_strlen(line) == 0)
		return (1);
	else 
		return (0);
	return (1);
}

static	void	parse(t_data *img, char *filename)
{
	t_list	*head;
	t_list	*tmp;
	char	*line;

	head = parse_map_cub(filename, img);
	tmp = head;
	while (tmp != NULL)
	{
		line = tmp->content;
		if (arg_parse(line, img) == 0)
			break ;
		tmp = tmp->next;
	}
	make_map(img, tmp, ft_lstsize(tmp));
	ft_lstclear(&head, &free);
}

static int		check_arguments(t_data *img)
{
	int count;

	count = 0;
	if (img->win.width != 0 && img->win.height != 0)
		count += 1;
	if (img->par.c != 0 && img->par.f != 0)
		count += 2;
	if (img->par.ea_img != 0 && img->par.no_img != 0 && img->par.s_img != 0
		&& img->par.so_img != 0 && img->par.we_img != 0)
		count += 5;
	if (count != 8)
		error_msg("Invalid arguments", img);
	return (1);
}

int				main(int argc, char **argv)
{
	t_data img;

	validate_input_argc(argv, argc, &img);
	ft_init(&img);
	parse(&img, argv[1]);
	if (check_arguments(&img) == 1)
		if (!validate_map(&img))
			error_msg("Invalid map", &img);
	img.win.mlx = mlx_init();
	if (load_textures(&img.tex, &img.win, &img.par) == 0)
		error_msg("Error texture", &img);
	ft_mlx_init(&img);
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
