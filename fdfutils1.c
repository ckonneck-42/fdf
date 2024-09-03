/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfutils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:22:21 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/03 17:21:39 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	numbercount(const char *filename, int *cols)
{
	int		count;
	int		fd;
	char	*line;
	char	*ptr;
	int		linecount;
	int		max_ints_in_line;
	int		current_ints_in_line;

	linecount = 0;
	max_ints_in_line = 0;
	current_ints_in_line = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		return (-1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		linecount++;
		current_ints_in_line = 0;
		ptr = line;
		while (*ptr)
		{
			if (ft_isdigit(*ptr) || (*ptr == '-' && ft_isdigit(*(ptr + 1))))
			{
				current_ints_in_line++;
				while (ft_isdigit(*ptr) || *ptr == '-')
					ptr++;
			}
			else
				ptr++;
		}
		if (current_ints_in_line > max_ints_in_line)
			max_ints_in_line = current_ints_in_line;
		free(line);
	}
	
	// ft_printf("lines: %d, numbers: %d\n",linecount, max_ints_in_line );
	close(fd);
	*cols = max_ints_in_line;
	return (linecount);
}

Coordinate	**allocateCoordinates(int rows, int cols)
{
	Coordinate	**coordinates;

	// Allocate memory for the array of pointers to rows
	coordinates = (Coordinate **)malloc(rows * sizeof(Coordinate *));
	if (coordinates == NULL)
	{
		ft_printf("Memory allocation failed for rows\n");
		exit(1);
	}
	// Allocate memory for each row
	for (int i = 0; i < rows; i++)
	{
		coordinates[i] = (Coordinate *)malloc(cols * sizeof(Coordinate));
		if (coordinates[i] == NULL)
		{
			ft_printf("Memory allocation failed for row %d\n", i);
			exit(1);
		}
		for (int j = 0; j < cols; j++)
        {
            coordinates[i][j].z = 2147483648; // Sentinel value
        }
	}
	return (coordinates);
}

void	addcoordinate(t_data *data, float x, float y, float z)
{

	data->coordinates[data->rows][data->cols].x = x;
	data->coordinates[data->rows][data->cols].y = y;
	data->coordinates[data->rows][data->cols].z = z;
}

void	freecall(Coordinate **coordinates, int rows)//fix for data
{
	for (int i = 0; i < rows; i++)
	{
		free(coordinates[i]); // Free each row
	}
	free(coordinates); // Free the array of pointers to rows
}