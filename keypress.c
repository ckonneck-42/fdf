/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:16:18 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/03 11:35:41 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//  K_ARRUP 65362
// # define K_ARRDWN 65364
// # define K_ARRLFT 65361
// # define K_ARRRGT 65363


int keypress(int keycode, t_data *data) {

    if (keycode == K_ARRLFT) // Left arrow key
        data->angle -= 0.1;
    else if (keycode == K_ARRRGT) // Right arrow key
        data->angle += 0.1;
    else if (keycode == K_ARRUP) // Up arrow key
        data->zoom += 0.1;
    else if (keycode == K_ARRDWN) // Down arrow key
        data->zoom -= 0.1;
    mlx_clear_window(data->mlx, data->win);
	// printf("zoom: %f\n", data->zoom);
    pixel2(data);
    
    return (0);
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

// 		my_mlx_pixel_put(data, data->x + (int)(i * dx), data->y + (int)(i * dy), data->colours, size);


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



// int	keypress(int keycode)
// {
// 	if (keycode == K_A)
// 	{
// 		ft_printf("a");
// 	}
// 	if (keycode == K_B)
// 	{
// 		ft_printf("b");
// 	}
// 	if (keycode == K_C)
// 	{
// 		ft_printf("c");
// 	}
// 	if (keycode == K_D)
// 	{
// 		ft_printf("d");
// 	}
// 	if (keycode == K_E)
// 	{
// 		ft_printf("e");
// 	}
// 	if (keycode == K_F)
// 	{
// 		ft_printf("f");
// 	}
// 	if (keycode == K_G)
// 	{
// 		ft_printf("g");
// 	}
// 	if (keycode == K_H)
// 	{
// 		ft_printf("h");
// 	}
// 	if (keycode == K_I)
// 	{
// 		ft_printf("i");
// 	}
// 	if (keycode == K_J)
// 	{
// 		ft_printf("j");
// 	}
// 	if (keycode == K_K)
// 	{
// 		ft_printf("k");
// 	}
// 	if (keycode == K_L)
// 	{
// 		ft_printf("l");
// 	}
// 	if (keycode == K_M)
// 	{
// 		ft_printf("m");
// 	}
// 	if (keycode == K_N)
// 	{
// 		ft_printf("n");
// 	}
// 	if (keycode == K_O)
// 	{
// 		ft_printf("o");
// 	}
// 	if (keycode == K_P)
// 	{
// 		ft_printf("p");
// 	}
// 	if (keycode == K_Q)
// 	{
// 		ft_printf("q");
// 	}
// 	if (keycode == K_R)
// 	{
// 		ft_printf("r");
// 	}
// 	if (keycode == K_S)
// 	{
// 		ft_printf("s");
// 	}
// 	if (keycode == K_T)
// 	{
// 		ft_printf("t");
// 	}
// 	if (keycode == K_U)
// 	{
// 		ft_printf("u");
// 	}
// 	if (keycode == K_V)
// 	{
// 		ft_printf("v");
// 	}
// 	if (keycode == K_W)
// 	{
// 		ft_printf("w");
// 	}
// 	if (keycode == K_X)
// 	{
// 		ft_printf("x");
// 	}
// 	if (keycode == K_Y)
// 	{
// 		ft_printf("y");
// 	}
// 	if (keycode == K_Z)
// 	{
// 		ft_printf("z");
// 	}
// 	if (keycode == K_ALT)
// 	{
// 		ft_printf("\ntudor sucks\n");
// 	}
	
// 	return (0);
// }
