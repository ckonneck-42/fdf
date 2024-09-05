/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:35:04 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/05 15:03:50 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CENTER_X 960
#define CENTER_Y 540
#define PI 3.14159265
#define K_L 108
#define K_M 109
#define K_P 112
#define K_ALT 65513
#define K_ARRUP 65362
#define K_ARRDWN 65364
#define K_ARRLFT 65361
#define K_ARRRGT 65363
#define K_ESC 65307
#define K_W 119
#define K_A 97
#define K_S 115
#define K_D 100

typedef struct t_Coordinate
{
	float			x;
	float			y;
	float			z;
}					t_Coordinate;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	float			x;
	float			y;
	float			z;
	float			x1;
	float			x2;
	float			y1;
	float			y2;
	float			z1;
	float			z2;
	float			line_x;
	float			line_y;
	float			line_z;
	float			line_dx;
	float			line_dy;
	float			colours;
	float			zoom;
	float			angle;
	float			angle_x;
	float			angle_y;
	float			angle_z;
	int				offset_x;
	int				offset_y;
	float			step;
	int				rows;
	int				cols;
	const char		*filename;
	int				check;
	int				mode;
	t_Coordinate	**coordinates;
}					t_data;

void				draw_point_iso(t_data *data, float source_x, float source_y,
						float source_z);
char				*hex_parsing(t_data *data, char *ptr);
int					ft_atoi_base(const char *str, int str_base);
void				validate_file(char **argv);
void				base_init(t_data *data);
int					close_window(t_data *data);
int					reinitialize_data(t_data *data);
char				*parse_and_pointer(t_data *data, char *ptr, char *z_str);
int					ft_close(int keycode, t_data *data);
char				*parse_init_rotation(t_data *data, char *ptr, char *z_str);
void				assign_coloums(t_data *data);
void				assign_rows(t_data *data);
void				translate_to_origin(float *x, float *y, float center_x,
						float center_y);
void				translate_back(float *x, float *y, float center_x,
						float center_y);
void				rotate_point_3d(t_data *data, float *x, float *y, float *z);
void				initialize_data(t_data *data, const char *filename);
void				rotate_point(float *x, float *y, float angle);
void				zoom_point(float *x, float *y, float zoom);
int					numbercount(const char *filename, int *cols);
void				draw_point(t_data *data, float source_x, float source_y,
						float source_z);
int					draw_map(t_data *data, const char *filename);
int					keypress(int keycode, t_data *data);
void				my_mlx_pixel_put(t_data *data, float x, float y, int size);
void				putlines(t_data *data);
void				freecall(t_Coordinate **coordinates, int rows);
t_Coordinate		**allocatecoordinates(int rows, int cols);
void				addcoordinate(t_data *data, float x, float y, float z);
