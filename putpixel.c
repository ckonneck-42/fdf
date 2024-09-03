/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:39:38 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/03 11:34:56 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


int	pixel2(t_data *data)
{


	ft_printf("coming from keypress");
	int fd;
	char *line;
	char *ptr;

	
	char *z_str;

	// ft_printf("lines: %d, numbers: %d",data->rows, data->cols );
	initialize_data(data);
	data->rows = 0;
	data->cols = 0;
    // Destroy the old image before creating a new one
    if (data->img != NULL) {
		ft_printf("destroying image\n");
        mlx_destroy_image(data->mlx, data->img);
    }
	fd = open("./test_maps/pyramide.fdf", O_RDONLY);
    data->img = mlx_new_image(data->mlx, 1920, 1080);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
   
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
					// printf("before zoom %f, %f\n", x, y);
					
                    zoom_point(&x, &y, data->zoom);
					// printf("after zoom %f, %f\n", x, y);
                    // Apply rotation
                    rotate_point(&x, &y, data->angle);
					draw_point(data, x, y, data->z, data->colours, 10, data->angle, data->coordinates, data->rows, data->cols);
					
					if (data->cols > 0 && data->coordinates[data->rows][data->cols-1].z != -1)
                        putlines(data, data->coordinates[data->rows][data->cols-1].x, data->coordinates[data->rows][data->cols].x,
							 data->coordinates[data->rows][data->cols-1].y, data->coordinates[data->rows][data->cols].y);
					if (data->rows > 0 && data->coordinates[data->rows-1][data->cols].z != -1)
						putlines(data, data->coordinates[data->rows-1][data->cols].x, data->coordinates[data->rows][data->cols].x,
							 data->coordinates[data->rows-1][data->cols].y, data->coordinates[data->rows][data->cols].y);
					

					data->x += 50;
                    ptr += ft_strlen(z_str);
					data->cols++;
				}
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
		// ft_printf("prevx: %d, rows: %d", data->prev_x, data->rows);
	}
		close(fd);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		freecall(data->coordinates, data->rows);
		ft_printf("cleared");
	return (0);
}

void draw_point(t_data *data, float source_x, float source_y, float source_z, int color, int size, float angle,
		Coordinate **coordinates, int rows, int cols ) {
    float destination_x = source_x * cos(angle) + source_y * cos(angle + 2) + source_z * cos(angle - 2);
    float destination_y = source_x * sin(angle) + source_y * sin(angle + 2) + source_z * sin(angle - 2);
	addcoordinate(data, destination_x, destination_y, source_z);
	//check printf here maybe
    my_mlx_pixel_put(data, destination_x, destination_y, color, size);

}
void putlines(t_data *data, float x1, float x2, float y1, float y2)
{
    float x, y, dx, dy, step;
    int i;

    dx = (x2 - x1);
    dy = (y2 - y1);

    if (fabs(dx) >= fabs(dy))
        step = fabs(dx);
    else
        step = fabs(dy);

    dx = dx / step;
    dy = dy / step;
    x = x1;
    y = y1;
    i = 1;
    while (i <= step)
    {	
		//  printf("Drawing line from (%f, %f) to (%f, %f)\n", x1, y1, x2, y2);
        my_mlx_pixel_put(data, (int)x, (int)y,16776960, 2);
        x = x + dx;
        y = y + dy;
        i = i + 1;
    }
}