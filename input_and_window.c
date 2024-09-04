/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_and_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:16:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/04 15:44:52 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	keypress(int keycode, t_data *data)
{
	if (keycode == K_ARRLFT)
		data->angle_y -= 0.1;
	else if (keycode == K_ARRRGT)
		data->angle_y += 0.1;
	else if (keycode == K_ARRUP)
		data->angle_x -= 0.1;
	else if (keycode == K_ARRDWN)
		data->angle_x += 0.1;
	else if (keycode == K_P)
		data->zoom += 0.1;
	else if (keycode == K_M)
		data->zoom -= 0.1;
	else if (keycode == K_W)
		data->offset_y -= 20;
	else if (keycode == K_A)
		data->offset_x -= 20;
	else if (keycode == K_S)
		data->offset_y += 20;
	else if (keycode == K_D)
		data->offset_x += 20;
	draw_map(data, data->filename);
	return (0);
}

int	ft_close(int keycode, t_data *data)
{
	int	i;

	if (keycode == K_ALT)
	{
		i = 0;
		while (i < 10)
		{
			ft_printf("i love tudor\n");
			i++;
		}
	}
	if (keycode == K_ESC)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}
	else
		return (0);
}

int	close_window(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_loop_end(data->mlx);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

// int	keypress(int keycode, t_data *data)
// {
// 	int size = 10; // Size of the square
// 	double angle_increment = 5; // 55 degrees in radians

// 	if (keycode == K_D)
// 	{
// 		data->angle -= angle_increment;
// 		data->colours += 30000;

// 		my_mlx_pixel_put(data, data->x, data->y, data->colours, 20);

// 	}
// 	else if (keycode == K_A)
// 	{
// 		data->angle += angle_increment;
// 		data->colours += 30000;

// 		my_mlx_pixel_put(data, data->x, data->y, data->colours, 20);

// 	}
// 	else if (keycode == K_W)
// 	{	data->colours += 30000;

// 			my_mlx_pixel_put(data, data->x, data->y, data->colours, 20);

// 	}
// 	else if (keycode == K_S)
// 	{	data->colours += 40000;

// 			my_mlx_pixel_put(data, data->x, data->y, data->colours, 20);

// 	}
// 	double dx = cos(data->angle);
// 	double dy = sin(data->angle);

// 	for (int i = 0; i < 100; i += size)

// 		my_mlx_pixel_put(data, data->x + (int)(i * dx), data->y + (int)(i * dy),
			//data->colours, size);

// 	data->x += (int)(100 * dx);
// 	data->y += (int)(100 * dy);

// 	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
// 	return (0);
// }

// int	keypress(int keycode, t_data *data)
// {
// 	int size = 10;
// 	if (keycode == K_D)
// 	{	data->colours += 1000000;
// 		for (int i = 0; i < 100; i++)
// 		{
// 			my_mlx_pixel_put(data, data->x + i, data->y, data->colours, 20);
// 		}
// 		data->x += 100;
// 	}
// 	else if (keycode == K_A)
// 	{	data->colours += 30000;
// 		for (int i = 0; i < 100; i++)
// 		{
// 			my_mlx_pixel_put(data, data->x - i, data->y, data->colours, 20);
// 		}
// 		data->x -= 100;
// 	}
// 	else if (keycode == K_W)
// 	{	data->colours += 30000;
// 		for (int i = 0; i < 100; i++)
// 		{
// 			my_mlx_pixel_put(data, data->x, data->y - i, data->colours, 20);
// 		}
// 		data->y -= 100;
// 	}
// 	else if (keycode == K_S)
// 	{	data->colours += 40000;
// 		for (int i = 0; i < 100; i++)
// 		{
// 			my_mlx_pixel_put(data, data->x, data->y + i, data->colours, 20);
// 		}
// 		data->y += 100;
// 	}
// 	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
// 	return (0);
// }
