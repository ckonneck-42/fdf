/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:32:12 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/04 17:25:47 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	validate_file(argv);
	data.filename = argv[1];
	base_init(&data);
	draw_map(&data, data.filename);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 2, 1L << 0, ft_close, &data);
	mlx_key_hook(data.win, keypress, &data);
	mlx_loop(data.mlx);
	return (0);
}

void base_init(t_data *data)
{
	data->map_width = 1920;
	data->map_height = 1080;
	data->check = 0;
	data->colours = 2290000;
	data->offset_x = 0;
	data->offset_y = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1920, 1080, "FdF");
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->angle = 0.0;
	data->angle_x = 0.0;
	data->angle_y = 0.0;
	data->zoom = 1;
}

void validate_file(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Couldn't read file \"%s\"\n", argv[1]);
		exit (-1);
	}
		
}
// data.colours = 16711680; // Red
// data.colours = 65280;    // Green
// data.colours = 255;      // Blue
// data.colours = 16776960; // Yellow
// data.colours = 16711935; // Magenta
// data.colours = 65535;    // Cyan
// data.colours = 16753920; // Orange
// data.colours = 8388736;  // Lime
// data.colours = 16761035; // Pink
// data.colours = 16744272; // Coral