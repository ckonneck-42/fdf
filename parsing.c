/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:39:38 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/04 15:44:39 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_data(t_data *data, const char *filename)
{
	data->cols = 0;
	data->rows = numbercount(data->filename, &data->cols);
	data->coordinates = allocateCoordinates(data->rows, data->cols);
	data->x = 960;
	data->y = 540;
}

int	reinitialize_data(t_data *data)
{
	int	fd;

	initialize_data(data, data->filename);
	data->rows = 0;
	data->cols = 0;
	fd = open(data->filename, O_RDONLY);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (fd);
}

void	assign_coloums(t_data *data)
{
	if (data->cols > 0 && data->coordinates[data->rows]
		[data->cols - 1].z != 2147483648)
	{
		data->x1 = data->coordinates[data->rows][data->cols - 1].x;
		data->x2 = data->coordinates[data->rows][data->cols].x;
		data->y1 = data->coordinates[data->rows][data->cols - 1].y;
		data->y2 = data->coordinates[data->rows][data->cols].y;
		data->z1 = data->coordinates[data->rows][data->cols - 1].z;
		data->z2 = data->coordinates[data->rows][data->cols].z;
		putlines(data);
	}
}

void	assign_rows(t_data *data)
{
	if (data->rows > 0 && data->coordinates[data->rows - 1]
		[data->cols].z != 2147483648)
	{
		data->x1 = data->coordinates[data->rows - 1][data->cols].x;
		data->x2 = data->coordinates[data->rows][data->cols].x;
		data->y1 = data->coordinates[data->rows - 1][data->cols].y;
		data->y2 = data->coordinates[data->rows][data->cols].y;
		data->z1 = data->coordinates[data->rows - 1][data->cols].z;
		data->z2 = data->coordinates[data->rows][data->cols].z;
		putlines(data);
	}
}

char	*parse_init_rotation(t_data *data, char *ptr, char *z_str)
{
	float	x;
	float	y;
	float	z;

	if (ft_strnstr(ptr, z_str, ft_strlen(z_str)))
	{
		x = data->x;
		y = data->y;
		z = data->z;
		zoom_point(&x, &y, data->zoom);
		translate_to_origin(&x, &y, CENTER_X, CENTER_Y);
		rotate_point_3d(data, &x, &y, &z);
		translate_back(&x, &y, CENTER_X, CENTER_Y);
		draw_point(data, x, y, data->z);
		assign_coloums(data);
		assign_rows(data);
		data->x += 50;
		ptr += ft_strlen(z_str);
		data->cols++;
	}
	return (ptr);
}
