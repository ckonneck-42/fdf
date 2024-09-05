/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:22:21 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/05 11:15:31 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_Coordinate	**allocatecoordinates(int rows, int cols)
{
	t_Coordinate	**coordinates;
	int				i;
	int				j;

	i = 0;
	coordinates = (t_Coordinate **)malloc(rows * sizeof(t_Coordinate *));
	if (coordinates == NULL)
	{
		ft_printf("Memory allocation failed for rows\n");
		exit(1);
	}
	while (i < rows)
	{
		coordinates[i] = (t_Coordinate *)malloc(cols * sizeof(t_Coordinate));
		if (coordinates[i] == NULL)
			exit(1);
		j = 0;
		while (j < cols)
		{
			coordinates[i][j].z = 2147483648;
			j++;
		}
		i++;
	}
	return (coordinates);
}

void	addcoordinate(t_data *data, float x, float y, float z)
{
	data->coordinates[data->rows][data->cols].x = x;
	data->coordinates[data->rows][data->cols].y = y;
	data->coordinates[data->rows][data->cols].z = z;
}

void	assign_coloums(t_data *data)
{
	if (data->cols > 0 && data->coordinates[data->rows]
		[data->cols - 1].z != 2147483648)
	{
		data->x1 = data->coordinates[data->rows][data->cols - 1].x;
		data->x2 = data->coordinates[data->rows][data->cols].x;
		data->y1 = data->coordinates[data->rows][data->cols - 1].y;
		data->y2 = data->coordinates[data->rows][data->cols].y;
		data->z1 = data->coordinates[data->rows][data->cols - 1].z;
		data->z2 = data->coordinates[data->rows][data->cols].z;
		putlines(data);
	}
}

void	assign_rows(t_data *data)
{
	if (data->rows > 0 && data->coordinates[data->rows - 1]
		[data->cols].z != 2147483648)
	{
		data->x1 = data->coordinates[data->rows - 1][data->cols].x;
		data->x2 = data->coordinates[data->rows][data->cols].x;
		data->y1 = data->coordinates[data->rows - 1][data->cols].y;
		data->y2 = data->coordinates[data->rows][data->cols].y;
		data->z1 = data->coordinates[data->rows - 1][data->cols].z;
		data->z2 = data->coordinates[data->rows][data->cols].z;
		putlines(data);
	}
}

void	freecall(t_Coordinate **coordinates, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(coordinates[i]);
		i++;
	}
	free(coordinates);
}
