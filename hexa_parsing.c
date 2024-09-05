/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:25:41 by ckonneck          #+#    #+#             */
/*   Updated: 2024/09/05 15:18:08 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_digit(char c, int digits_in_base)
{
	int	max_digit;

	if (digits_in_base <= 10)
		max_digit = digits_in_base - 1 + '0';
	else
		max_digit = digits_in_base - 10 - 1 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;
	int	digit;

	result = 0;
	sign = 1;
	if (str == NULL || str_base < 2 || str_base > 16)
		return (0);
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	while (*str)
	{
		digit = get_digit(ft_tolower(*str), str_base);
		if (digit == -1)
			break ;
		result = result * str_base + digit;
		++str;
	}
	return (result * sign);
}

char	*hex_parsing(t_data *data, char *ptr)
{
	char	hex_str[9];
	int		i;

	data->check = 1;
	ptr++;
	i = 0;
	while (*ptr != ' ' && *ptr != '\0' && i < 8)
		hex_str[i++] = *ptr++;
	hex_str[i] = '\0';
	if (hex_str[0] == '0' && hex_str[1] == 'x')
		data->colours = ft_atoi_base(hex_str + 2, 16);
	else
		data->colours = ft_atoi_base(hex_str, 16);
	if (data->cols == 1 && data->rows != 0)
		putlines(data);
	return (ptr);
}

// // isometric projection
void	draw_point_iso(t_data *data, float source_x,
		float source_y, float source_z)
{
	float	projected_x;
	float	projected_y;

	data->angle = PI / 6;
	projected_x = (source_x - source_y) * cos(data->angle);
	projected_y = (source_x + source_y) * sin(data->angle) - source_z;
	addcoordinate(data, projected_x + data->offset_x, projected_y
		+ data->offset_y, source_z);
}
