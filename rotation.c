/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:12:25 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/04 14:23:10 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_point(float *x, float *y, float angle)
{
	float	temp_x;

	temp_x = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = temp_x * sin(angle) + *y * cos(angle);
}

void	zoom_point(float *x, float *y, float zoom)
{
	*x -= CENTER_X;
	*y -= CENTER_Y;
	*x *= zoom;
	*y *= zoom;
	*x += CENTER_X;
	*y += CENTER_Y;
}

void	rotate_point_3d(t_data *data, float *x, float *y, float *z)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;

	temp_x = *x;
	temp_y = *y;
	temp_z = *z;
	*y = temp_y * cos(data->angle_x) - temp_z * sin(data->angle_x);
	*x = temp_x * cos(data->angle_y) + temp_z * sin(data->angle_y);
}

// *z = temp_y * sin(data->angle_x) + temp_z * cos(data->angle_x);
// *z = -temp_x * sin(data->angle_y) + temp_z * cos(data->angle_y);
void	translate_to_origin(float *x, float *y, float center_x, float center_y)
{
	*x -= center_x;
	*y -= center_y;
}

void	translate_back(float *x, float *y, float center_x, float center_y)
{
	*x += center_x;
	*y += center_y;
}
