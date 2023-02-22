/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 21:50:05 by hkaddour          #+#    #+#             */
/*   Updated: 2023/02/22 15:10:11 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# define ELEM "NO SO EA WE F C"
//# define  "E N W S"
# define WIN_W 1366
# define WIN_H 768
# define SPEED 5.0
# define ROT_SPEED 5.0
# define FOV 60
# define SQR_SIZE 50
//# define SQR_SIZE 64
# define ROT_RIGHT 123
# define ROT_LEFT 124
# define RIGHT 2
# define LEFT 0
# define UP 13
# define DOWN 1
# define VIEW_UP 126
# define VIEW_DOWN 125
# define ESC 53
//# define INT_MAX 2147483647
# include "../libft/libft.h"
# include "../gnl/gnl.h"
# include "draw.h"

int	H_T;
int	W_T;

typedef struct image_utils t_img;

typedef struct s_coordinate t_coord;

typedef struct s_keys	t_keys;

typedef struct s_camera	t_cam;

typedef struct player_stat
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
} p_stat;

typedef struct s_color
{
	int	floor;
	int	ceiling;
} t_color;

typedef struct s_free
{
	void	*value;
	struct s_free *next;
} t_free;

typedef	struct s_map
{
	int		player_exist;
	char	player;
	int		width;
	int		height;
	char	**map;
} t_map;

typedef struct s_mlx
{
	void	*init;
	void	*win;
	t_img	*utils;
} t_mlx;

typedef struct s_data
{
	char		*n_file;
	int			fd_map;
	char		**r_file;
	t_img		*texture;
	//t_key		*keys;
	p_stat	*ply_stat;
	t_color	*color;
	t_map		*map;
	t_mlx		*mlx;
	t_coord	*draw_utils;
	t_keys	*key_mv;
	t_cam		*ray;
	t_free	*g_collect;
} t_data;


/******** Function of main **********/
void	init_data(t_data *data, char *file);
void	*allocation(t_data *data, int count, int size);
char	*add_dup(t_data *data, char *s);

/******** Function of error **********/
void	error_alloc(void);
void	error_file(char *msg);

/******** Function of free **********/
void	garbage_collector(t_data *data, void *addr);
void	free_all(t_data *data);

/******** Function of parsing **********/
void	read_file(t_data *data);
void	parse_file(t_data *data);
char	*add_texture_elem(t_data *data, char *file);
int		color_converter(t_data *data, char **rgb);
void	parse_map(t_data *data, char **map);
void	check_map_error(t_data *data);
void	check_color(t_data *data, int i, char *line);
//void	check_texture(t_data *data, char *line);
void	check_texture(t_data *data, int j, char *line);
int		add_color_elem(t_data *data, char *line);

/******** Function of drawing **********/
void	window_init(t_data *data);
void	einstein_drawing(t_data *data);
void	catch_player_pos(t_data *data);
void	make_and_init_image(t_data *data);
void	mlx_put_pixel_to_img(t_data *data, int x, int y, int clr);
void	draw_rays(t_data *data);
void	dda(t_data *data, int	loun);

int	did_it_hit_the_wall(t_data *data, double coord1, double coord2);
void	look_im_3d_now(t_data *data, double angle);
void	get_textures(t_data *data);
unsigned int	texture_clr(t_data *data, int x);

/******** Function of Keys **********/
int	keys(t_data *data);
int	close_win(t_data *data);

/******** Function of Math **********/
double	convert_deg2rad(double degree);
double	convert_rad2deg(double radians);
//void		chk_degree_low_or_high(double angle);

#endif
