/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:35:04 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/03 11:33:28 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/libft.h"
#include <mlx.h>
#include <stdlib.h>
#include <math.h>
# include <unistd.h>
# include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#define PI 3.14159265
#ifndef Keycode
#define Keycode
/* --- Movement Keys --- */
# define K_A 97
# define K_B 98
# define K_C 99
# define K_D 100
# define K_E 101
# define K_F 102
# define K_G 103
# define K_H 104
# define K_I 105
# define K_J 106
# define K_K 107
# define K_L 108
# define K_M 109
# define K_N 110
# define K_O 111
# define K_P 112
# define K_Q 113
# define K_R 114
# define K_S 115
# define K_T 116
# define K_U 117
# define K_V 118
# define K_W 119
# define K_X 120
# define K_Y 121
# define K_Z 122
# define K_ALT 65513
# define K_ARRUP 65362
# define K_ARRDWN 65364
# define K_ARRLFT 65361
# define K_ARRRGT 65363

/* --- closing window --- */
# define K_ESC 65307


typedef struct Coordinate
{
    float x;
	float y;
	float z;
} 				Coordinate;


typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	float		x;
	float		y;
	float		z;
	int		colours;
	int		prev_x;
	float		prev_y;
	float		prev_z;
	float		zoom;
	float		angle;
	int		rows;
	int		cols;
	const char	*filename;
	Coordinate **coordinates;
}				t_data;



typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


void initialize_data(t_data *data);
void rotate_point(float *x, float *y, float angle);
void zoom_point(float *x, float *y, float zoom);
int	numbercount(const char *filename, int *cols);
void draw_point(t_data *data, float source_x, float source_y, float source_z, int color, int size, float angle,
		Coordinate **coordinates, int rows, int cols );
int	pixel2(t_data *data);
int keypress(int keycode, t_data *data);

void	my_mlx_pixel_put(t_data *data, float x, float y, int color, int size);
void putlines(t_data *data, float x1, float x2, float y1, float y2);
void freecall(Coordinate **coordinates, int rows);
Coordinate **allocateCoordinates(int rows, int cols);
void	addcoordinate(t_data *data, float x, float y, float z);
#endif