/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:39:38 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/03 18:38:03 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


int	pixel2(t_data *data, const char *filename)
{
	int fd;
	char *line;
	char *ptr;
	float center_x;
	float center_y;
	char *z_str;

	initialize_data(data, data->filename);
	data->rows = 0;
	data->cols = 0;
	// mlx_clear_window(data->mlx, data->win);
    // if (data->img != NULL)
    //     mlx_destroy_image(data->mlx, data->img);
	fd = open(filename, O_RDONLY);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, 1920, 1080);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    calculate_center(data, &center_x, &center_y);
	while ((line = get_next_line(fd)) != NULL)
	{
		ptr = line;
		while (*ptr)
		{
			if(ft_isdigit(*ptr) || (*ptr == '-' && ft_isdigit(*(ptr + 1))))
			{
				data->z = atoi(ptr);
				z_str = ft_itoa(data->z);

				if (ft_strnstr(ptr, z_str, ft_strlen(z_str)))
				{			
						if(data->z == 0)
						data->colours =16711680;
						else
						data->colours = 65535*data->z;
					float x = data->x;
                    float y = data->y;
					float z = data->z;
					// printf("before zoom %f, %f\n", x, y);
                    zoom_point(&x, &y, data->zoom);
					// printf("after zoom %f, %f\n", x, y);
                    // Apply rotation
					translate_to_origin(&x, &y, center_x, center_y);
                    rotate_point(&x, &y, data->angle);
					rotate_point_3d(&x, &y, &z, data->angle_x, data->angle_y);
					translate_back(&x, &y, center_x, center_y);
					draw_point(data, x, y, data->z, data->colours, 0, data->angle, data->coordinates,
								data->angle_x, data->angle_y);
					
					if (data->cols > 0 && data->coordinates[data->rows][data->cols-1].z != 2147483648)
                        putlines(data, data->coordinates[data->rows][data->cols-1].x,
								data->coordinates[data->rows][data->cols].x,
								data->coordinates[data->rows][data->cols-1].y,
								data->coordinates[data->rows][data->cols].y,
								data->coordinates[data->rows][data->cols-1].z,
								data->coordinates[data->rows][data->cols].z);
					if (data->rows > 0 && data->coordinates[data->rows-1][data->cols].z != 2147483648)
						putlines(data, data->coordinates[data->rows-1][data->cols].x,
								data->coordinates[data->rows][data->cols].x,
								data->coordinates[data->rows-1][data->cols].y,
								data->coordinates[data->rows][data->cols].y,
								 data->coordinates[data->rows-1][data->cols].z,
								 data->coordinates[data->rows][data->cols].z);
					

					data->x += 50;
                    ptr += ft_strlen(z_str);
					data->cols++;
				}
				free(z_str);
			}
			else
			{
				ptr += 1;
			}
		}
		free(line);
		data->cols = 0;
		data->rows++;
		data->x = 700;
		data->y += 50;
		printf("zoom is %f", data->zoom);
	}
		close(fd);
		
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		freecall(data->coordinates, data->rows);
	return (0);
}

void draw_point(t_data *data, float source_x, float source_y, float source_z, int color, int size, float angle,
		Coordinate **coordinates, float angle_x, float angle_y ) {

	float projected_x = source_x * cos(angle) + source_y * cos(angle + 2) + source_z * cos(angle - 2);
    float projected_y = source_x * sin(angle) + source_y * sin(angle + 2) + source_z * sin(angle - 2);
	addcoordinate(data, projected_x, projected_y, source_z);
	
    my_mlx_pixel_put(data, projected_x, projected_y, color, size);

}

void draw_pointiso(t_data *data, float source_x, float source_y, float source_z, int color, int size, float angle,
		Coordinate **coordinates, float angle_x, float angle_y ) {

		float projected_x = source_x + cos(angle) * source_z;
		float projected_y = source_y + sin(angle) * source_z;
	addcoordinate(data, projected_x, projected_y, source_z);
	
    my_mlx_pixel_put(data, projected_x, projected_y, color, size);

}
void putlines(t_data *data, float x1, float x2, float y1, float y2, float z1, float z2)
{
    float x, y, dx, dy, step;
    int i;
	int color;
    dx = (x2 - x1);
    dy = (y2 - y1);

    if (fabs(dx) > fabs(dy))
        step = fabs(dx);
    else
        step = fabs(dy);
	// if (step == 0)
	//  	step = 1; // Avoid division by zero
    dx = dx / step;
    dy = dy / step;
    x = x1;
    y = y1;
    i = 1;
    while (i <= step)
    {	
		float z = z1 + (z2 - z1) * ((float)i / step);
		if(z == 0)
			data->colours =16711680;
		else
			data->colours = 65535* fabs(z);
        my_mlx_pixel_put(data, (int)x, (int)y, data->colours, 2);//change colour based off height
        x = x + dx;
        y = y + dy;
        i = i + 1;
    }
}