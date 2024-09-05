/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:39:38 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/05 15:11:11 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	reinitialize_data(t_data *data)
{
	int	fd;

	initialize_data(data, data->filename);
	data->rows = 0;
	data->cols = 0;
	fd = open(data->filename, O_RDONLY);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (fd);
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
		if (data->mode == 1)
			draw_point(data, x, y, data->z);
		else
			draw_point_iso(data, x, y, data->z);
		assign_coloums(data);
		assign_rows(data);
		data->check = 0;
		data->x += 50;
		ptr += ft_strlen(z_str);
		data->cols++;
	}
	return (ptr);
}

char	*numbercount3(char *ptr, int *current_ints_in_line)
{
	if (ft_isdigit(*ptr) || (*ptr == '-' && ft_isdigit(*(ptr + 1))))
	{
		(*current_ints_in_line)++;
		while (ft_isdigit(*ptr) || *ptr == '-')
			ptr++;
	}
	else
		ptr++;
	return (ptr);
}

int	numbercount2(int *linecount, int fd, char *ptr, int current_ints_in_line)
{
	int		max_ints_in_line;
	char	*line;

	max_ints_in_line = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		(*linecount)++;
		current_ints_in_line = 0;
		ptr = line;
		while (*ptr)
			ptr = numbercount3(ptr, &current_ints_in_line);
		if (current_ints_in_line > max_ints_in_line)
			max_ints_in_line = current_ints_in_line;
		free(line);
		line = get_next_line(fd);
	}
	return (max_ints_in_line);
}

int	numbercount(const char *filename, int *cols)
{
	int		fd;
	char	*ptr;
	int		linecount;
	int		max_ints_in_line;
	int		current_ints_in_line;

	current_ints_in_line = 0;
	max_ints_in_line = 0;
	linecount = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	max_ints_in_line = numbercount2(&linecount, fd, ptr, current_ints_in_line);
	close(fd);
	*cols = max_ints_in_line;
	return (linecount);
}
