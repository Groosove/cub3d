/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavon <flavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 13:23:13 by flavon            #+#    #+#             */
/*   Updated: 2020/10/16 14:47:53 by flavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCALE 20

# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define R_LEFT 123
# define R_RIGHT 124

# define FOV 66

# include "../minilibx_mms/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

typedef struct		s_paint
{
	double			wall_x;
	double			step;
	double			tex_pos;
	int				tex_x;
	int				tex_y;
	int				tex_h;
	int				tex_w;
}					t_paint;

typedef	struct		s_map
{
	char			*line;
	char			**map;
	int				x;
	int 			y;
}					t_map;

typedef	struct		s_raycast
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	double			r_d_x;
	double			r_d_y;
	double			plane_x;
	double			plane_y;
	double			dist_x;
	double			dist_y;
	double			dlt_d_x;
	double			dlt_d_y;
	double			player_x;
	double			player_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				wall_start;
	int				wall_height;
	int				wall_end;
	int				wall_side;
	double			wall_dist;
	double			*buffer;
}					t_raycast;

typedef struct		s_ray_sp
{
	double			sprite_x;
	double			sprite_y;
	double			invdet;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_h;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_w;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
	int				sprite;
}					t_ray_sp;

typedef struct		s_sprite
{
	int				index;
	double			x;
	double			y;
	double			dist;
}					t_sprite;

typedef struct		s_key
{
	int				up;
	int				right;
	int 			down;
	int				left;
	int				r_left;
	int				r_right;
}					t_key;

typedef	struct		s_win
{
	void			*img;
	char			*addr;
	int				bit_pix;
	int				length;
	int				endian;
	void			*win;
	void			*mlx;
	int				width;
	int				height;
}					t_win;

typedef struct		s_param
{
	char 			*no_img;
	char 			*so_img;
	char 			*we_img;
	char			*ea_img;
	char			*s_img;
	unsigned long	f_col;
	unsigned long	c_col;
	char			dir;
	int				f;
	int				c;
}					t_param;

typedef struct		s_texture
{
	t_win			no_tex;
	t_win			so_tex;
	t_win			we_tex;
	t_win			ea_tex;
	t_win			s_tex;
}					t_texture;

typedef struct		s_data
{
	t_win			win;
	t_key			key;
	t_sprite		*sprite;
	t_param			par;
	t_texture		tex;
	t_raycast		ray;
	t_paint			paint;
	t_ray_sp		sp_ray;
	t_map			map;
	int				sprite_count;
}					t_data;

char				**parse_map(char *filename);
void				make_map(t_data *img, t_list **head, int size);
int					load_textures(t_texture *tex, t_win *win, t_param *par);
int					sprite_init(t_data *img, int x, int y);
unsigned long		ft_calc_color(char *src, int *flag, t_data *img);
void				error_msg(char *dst, t_data *img);
int					ft_exit(t_data *img);
void				ft_raycast(t_data *img);
void				calc_player(t_data *img);
int					ft_screen_shot(t_data *img);

void				validate_input_argc(char **argv, int argc, t_data *img);
void				create_window(t_data *img);
void				ft_mlx_init(t_data *img);
void				ft_get_param(char *src, t_data *img);

void				ft_init(t_data *img);
void				init_keys(t_key *key);
void				init_param(t_param *param);

void				way_down(t_raycast *ray, t_map *map);
void				way_up(t_raycast *ray, t_map *map);
void				way_left(t_raycast *ray, t_map *map);
void				way_right(t_raycast *ray, t_map *map);
void				ft_rotate(t_raycast *ray, double cosinus);

int					ft_run(t_data *img);
int					ft_key_release(int key, t_data *img);
int					ft_key_code(int key, t_data *img);
int					check_map_step(char **map, int x, int y);

int					validate_map(t_data *img);
void				print_background(t_data *img, int x);
int					ft_get_color(t_win *img, int x, int y);
void				ft_get_sprite(t_data *img);
void				ft_print_wall(t_data *img, int x);
void				ft_pixel_put(t_data *img, int x, int y, int color);
void				ft_calc_step(t_raycast *ray);
void				ft_check_space(t_data *img);
void				ft_free(t_data *img);
void				ft_free_line(void *content);
#endif
