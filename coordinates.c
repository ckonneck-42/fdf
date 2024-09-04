/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfutils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:22:21 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/04 13:05:44 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	numbercount2(int *linecount, int fd, char *ptr, int current_ints_in_line)
{
	int		max_ints_in_line;
	char	*line;

	max_ints_in_line = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		(*linecount)++;
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
	return(max_ints_in_line);
}

int	numbercount(const char *filename, int *cols)
{
	int		fd;
	char	*ptr;
	int		linecount;
	int		max_ints_in_line;
	int		current_ints_in_line;

	current_ints_in_line = 0;
	max_ints_in_line = 0;
	linecount = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	max_ints_in_line = numbercount2(&linecount, fd, ptr, current_ints_in_line);
	close(fd);
	*cols = max_ints_in_line;
	return (linecount);
}

t_Coordinate	**allocateCoordinates(int rows, int cols)
{
	t_Coordinate	**coordinates;

	// Allocate memory for the array of pointers to rows
	coordinates = (t_Coordinate **)malloc(rows * sizeof(t_Coordinate *));
	if (coordinates == NULL)
	{
		ft_printf("Memory allocation failed for rows\n");
		exit(1);
	}
	// Allocate memory for each row
	for (int i = 0; i < rows; i++)
	{
		coordinates[i] = (t_Coordinate *)malloc(cols * sizeof(t_Coordinate));
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

void	freecall(t_Coordinate **coordinates, int rows)
{
	int i;

	i = 0;
	while(i < rows)
	{
		free(coordinates[i]);
		i++;
	}
	free(coordinates);
}
