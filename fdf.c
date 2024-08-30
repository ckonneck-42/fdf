/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:32:12 by ckonneck          #+#    #+#             */
/*   Updated: 2024/08/30 15:30:43 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color, int size)
{
	char	*dst;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (x + i >= 0 && x + i < 1920 && y + j >= 0 && y + j < 1080) {
				dst = data->addr + ((y + j) * data->line_length + (x + i) * (data->bits_per_pixel / 8));
				*(unsigned int*)dst = color;
			}
		}
	}
}
int	ft_close(int keycode, t_vars *vars)
{
		if (keycode == K_ALT)
	{
		int i = 0;
		while ( i <10)
		{
			ft_printf("i love tudor\n");
			i++;
		}
		
	}
	if (keycode == K_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else
		return (0);
}

// int	notify(void)
// {
// 	ft_printf("you in\n");
// 	return (0);
// }

// int	notify2(void)
// {
// 	ft_printf("you out\n");
// 	return (0);
// }

// int	mouse_hook(int button, int x, int y, t_vars *vars)
// {
// 	ft_printf("Mouse button %d pressed at (%d, %d)\n", button, x, y);
// 	return (0);
// }

// int	mouse_move(int x, int y, t_vars *vars)
// {
// 	ft_printf("Mouse moved to (%d, %d)\n", x, y);
// 	return (0);
// }
// int	render_next_frame(t_data *data)
// {
// 	// Clear the image
// 	mlx_clear_window(data->mlx, data->win);

// 	// Update the position or any other variables
// 	data->x += 1;
// 	data->y += 1;
// 	// Draw something at the new position
// 	my_mlx_pixel_put(data, data->x, data->y, 0x00FF00, 10);

// 	// Put the image to the window
// 	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

// 	return (0);
// }



int	main(void)
{
	t_data	data;
	t_vars	vars;
	data.colours = 2290000;//turquoise
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data.x = 700;//
	data.y = 300;// 
	vars.mlx = data.mlx;
	vars.win = data.win;
	// pixel(&data);
	pixel2(&data);
	mlx_hook(vars.win, 2, 1L << 0, ft_close, &vars);
	// mlx_key_hook(data.win, keypress, &data);
	mlx_loop(data.mlx);
	
	return (0);
}


// 	t_vars vars;

	// vars.mlx = mlx_init();
	// vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	// mlx_hook(vars.win, 2, 1L << 0, ft_close, &vars);
	// mlx_hook(vars.win, 7, 1L << 4, notify, &vars);
	// mlx_hook(vars.win, 8, 1L << 5, notify2, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_hook(vars.win, 6, 1L << 6, mouse_move, &vars); // 1L<<6 is the mask for mouse motion
	// mlx_key_hook(vars.win, keypress, &vars);
	// mlx_loop(vars.mlx);

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