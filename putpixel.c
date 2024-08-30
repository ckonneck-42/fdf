/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:39:38 by ckonneck          #+#    #+#             */
/*   Updated: 2024/08/30 15:35:44 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	pixel2(t_data *data)
{
	int fd;
	int i;
	char *line;
	char *ptr;

	fd = open("./test_maps/10-70.fdf", O_RDONLY);
	i = 0;
	char *z_str;


	
	while ((line = get_next_line(fd)) != NULL)
	{
		char *ptr = line;
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
					draw_point(data, data->x, data->y, data->z, data->colours, 10, 0.11);
					// Adjust the angle as needed
						// movable
						
					if (i >= 0)
                        putlines(data, data->prev_x, data->prev_y, data->prev_z, data->x, data->y, data->z);

					//need a ft that actually takes z, or directly converts it
					mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);//need to look more into that.
					data->x += 50;
                    ptr += ft_strlen(z_str);
                    i++;
					
				}
			}
			else
			{
				ptr += 1;
			}
				
		}
		data->x = 700;
		data->y += 50;
	}
	return (0);
}

void draw_point(t_data *data, float source_x, float source_y, float source_z, int color, int size, float angle) {
    float destination_x = source_x * cos(angle) + source_y * cos(angle + 2) + source_z * cos(angle - 2);
    float destination_y = source_x * sin(angle) + source_y * sin(angle + 2) + source_z * sin(angle - 2);

    my_mlx_pixel_put(data, (int)destination_x, (int)destination_y, color, size);

    // Store the current coordinates for the next line
    data->prev_x = destination_x;
    data->prev_y = destination_y;
    data->prev_z = source_z;
}
void putlines(t_data *data, float x1, float y1, float z1, float x2, float y2, float z2) {
    float x, y, z, dx, dy, dz, step;
    int i;

    dx = (x2 - x1);
    dy = (y2 - y1);
    dz = (z2 - z1);

    if (fabs(dx) >= fabs(dy) && fabs(dx) >= fabs(dz))
        step = fabs(dx);
    else if (fabs(dy) >= fabs(dx) && fabs(dy) >= fabs(dz))
        step = fabs(dy);
    else
        step = fabs(dz);

    dx = dx / step;
    dy = dy / step;
    dz = dz / step;
    x = x1;
    y = y1;
    z = z1;
    i = 1;
    while (i <= step) {
        my_mlx_pixel_put(data, (int)x, (int)y, 2793462, 2);
        x = x + dx;
        y = y + dy;
        z = z + dz;
        i = i + 1;
    }
}
