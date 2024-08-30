int	keypress(int keycode, t_data *data)
{
	int i = -1000000;
	while (i <1000000)
	{
		int size = 10; // Size of the square
	double angle_increment = 5; // 55 degrees in radians


		data->angle -= angle_increment;
		data->colours += 30000;

		my_mlx_pixel_put(data, data->x, data->y, data->colours, 20);






	
	data->colours += 40000;
	
			my_mlx_pixel_put(data, data->x, data->y, data->colours, 20);

		double dx = cos(data->angle);
	double dy = sin(data->angle);

	for (int i = 0; i < 1000; i += size)
		my_mlx_pixel_put(data, data->x + (int)(i * dx), data->y + (int)(i * dy), data->colours, size);


	data->x += (int)(100 * dx);
	data->y += (int)(100 * dy);

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	i++;
	}
	
	return (0);
}