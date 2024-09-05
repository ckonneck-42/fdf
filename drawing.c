/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:02:05 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/05 15:18:26 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_map(t_data *data, const char *filename)
{
	int		fd;
	char	*line;
	char	*ptr;
	char	*z_str;

	fd = reinitialize_data(data);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ptr = line;
		while (*ptr)
			ptr = parse_and_pointer(data, ptr, z_str);
		free(line);
		data->cols = 0;
		data->rows++;
		data->x = 960;
		data->y += 50;
		line = get_next_line(fd);
	}
	close(fd);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	freecall(data->coordinates, data->rows);
	return (0);
}

void	draw_point(t_data *data, float source_x, float source_y, float source_z)
{
	float	projected_x;
	float	projected_y;

	projected_x = source_x * cos(data->angle) + source_y * cos(data->angle + 2)
		+ source_z * cos(data->angle - 2);
	projected_y = source_x * sin(data->angle) + source_y * sin(data->angle + 2)
		+ source_z * sin(data->angle - 2);
	addcoordinate(data, projected_x + data->offset_x, projected_y
		+ data->offset_y, source_z);
}
// my_mlx_pixel_put(data, projected_x, projected_y, 0);

void	putlines(t_data *data)
{
	int	i;

	data->line_dx = (data->x2 - data->x1);
	data->line_dy = (data->y2 - data->y1);
	if (fabs(data->line_dx) > fabs(data->line_dy))
		data->step = fabs(data->line_dx);
	else
		data->step = fabs(data->line_dy);
	data->line_dx = data->line_dx / data->step;
	data->line_dy = data->line_dy / data->step;
	data->line_x = data->x1;
	data->line_y = data->y1;
	i = 1;
	while (i <= data->step)
	{
		data->line_z = data->z1 + (data->z2 - data->z1) * (i / data->step);
		if (data->line_z == 0 && data->check != 1)
			data->colours = 16711680;
		else if (data->check != 1)
			data->colours = 65535 * data->line_z;
		my_mlx_pixel_put(data, data->line_x, data->line_y, 5);
		data->line_x = data->line_x + data->line_dx;
		data->line_y = data->line_y + data->line_dy;
		i++;
	}
}

char	*parse_and_pointer(t_data *data, char *ptr, char *z_str)
{
	if (ft_isdigit(*ptr) || (*ptr == '-' && ft_isdigit(*(ptr + 1))))
	{
		data->z = ft_atoi(ptr);
		z_str = ft_itoa(data->z);
		ptr = parse_init_rotation(data, ptr, z_str);
		free(z_str);
	}
	else if (*ptr == ',')
		ptr = hex_parsing(data, ptr);
	else
		ptr++;
	return (ptr);
}

void	my_mlx_pixel_put(t_data *data, float x, float y, int size)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i >= 0 && x + i < 1920 && y + j >= 0 && y + j < 1080)
			{
				dst = data->addr + ((int)(y + j) *data->line_length + (int)(x
							+ i) *(data->bits_per_pixel / 8));
				*(unsigned int *)dst = data->colours;
			}
			j++;
		}
		i++;
	}
}
