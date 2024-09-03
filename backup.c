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
        draw_point(data, (int)x, (int)y, 0, 2793462, 1, 0.11);
        x = x + dx;
        y = y + dy;
        i = i + 1;
    }
}


#include "fdf.h"
#include <stdio.h>

int	pixel2(t_data *data)
{
	int fd;
	int i;
	char *line;
	char *ptr;

	fd = open("./test_maps/42.fdf", O_RDONLY);
	i = 0;
	char *z_str;
	int cols = 0;
	int rows = numbercount("./test_maps/42.fdf", &cols);
	ft_printf("lines: %d, numbers: %d",rows, cols );
	Coordinate **coordinates = allocateCoordinates(rows, cols);
	rows = 0;
	cols = 0;
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
					ft_printf("before x: %d, y: %d\n", data->x, data->y);
					draw_point(data, data->x, data->y, data->z, data->colours, 10, 0.11, coordinates, rows, cols);
					
					
					cols++;
					if (i > 0)
                        putlines(data, coordinates[rows][cols-1].x, coordinates[rows][cols-1].y,
							coordinates[rows][cols-1].z, coordinates[rows][cols].x, coordinates[rows][cols].y,
							coordinates[rows][cols].z);

					//need a ft that actually takes z, or directly converts it
					mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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
		cols = 0;
		rows++;
		data->x = 700;
		data->y += 50;
	}
	//  ft_printf("Coordinate at (3, 5): x = %d, y = %d, z = %d\n",
    //        coordinates[3][5].x, coordinates[3][5].y, coordinates[3][5].z);
	freecall(coordinates, rows);
	return (0);
}

void draw_point(t_data *data, float source_x, float source_y, float source_z, int color, int size, float angle,
		Coordinate **coordinates, int rows, int cols ) {
    float destination_x = source_x * cos(angle) + source_y * cos(angle + 2) + source_z * cos(angle - 2);
    float destination_y = source_x * sin(angle) + source_y * sin(angle + 2) + source_z * sin(angle - 2);
	addcoordinate(coordinates, destination_x, destination_y, rows, cols);
	ft_printf("after x: %d, y: %d\n", data->x, data->y);
    my_mlx_pixel_put(data, (int)destination_x, (int)destination_y, color, size);
	
    // Store the current coordinates for the next line
    // data->prev_x = destination_x;
    // data->prev_y = destination_y;
    // data->prev_z = source_z;
}
void putlines(t_data *data, int x1, int y1, int z1, int x2, int y2, int z2) {
    int x, y, z, dx, dy, dz, step;
    int i;

    dx = (x2 - x1);
    dy = (y2 - y1);
    dz = (z2 - z1);

    if (abs(dx) >= abs(dy) && abs(dx) >= abs(dz))
        step = abs(dx);
    else if (abs(dy) >= abs(dx) && abs(dy) >= abs(dz))
        step = abs(dy);
    else
        step = abs(dz);

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

