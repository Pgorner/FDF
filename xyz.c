/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:49:06 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/15 15:03:10 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_ms(t_s *ms)
{
	int	i;

	i = 0;
	while (i <= ms->height)
	{
		free(ms->x[i]);
		free(ms->y[i]);
		free(ms->z[i]);
		++i;
	}
	free(ms->x);
	free(ms->y);
	free(ms->z);
	i = 0;
	while (i <= ms->height * ms->width)
		free(ms->map[i++]);
	free(ms->map);
	free(ms);
}

void	safe_exit(t_s *ms)
{
	mlx_close_window(ms->mlx);
	free_ms(ms);
	exit(EXIT_SUCCESS);
}

void	x(t_s *ms)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	ms->x = ft_calloc(sizeof(int), ms->width * ms->height);
	while (i <= ms->height)
		ms->x[i++] = ft_calloc(sizeof(int), ms->width + 1);
	i = 0;
	while (i < ms->height)
	{
		j = 0;
		while (j < ms->width)
		{
			if (j == 0)
				ms->x[i][j] = ms->sx;
			else
				ms->x[i][j] += ms->sx + (ms->offset * j);
			++j;
		}
		++i;
	}
}

void	y(t_s *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ms->y = ft_calloc(sizeof(int), ms->width * ms->height);
	while (i <= ms->height)
		ms->y[i++] = ft_calloc(sizeof(int), ms->width);
	i = 0;
	while (i < ms->height)
	{
		j = 0;
		while (j < ms->width)
		{
			ms->y[i][j] = ms->sy + (ms->offset * i);
			++j;
		}
		++i;
	}
}

void	z(t_s *ms)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	ms->z = ft_calloc(sizeof(int), ms->width * ms->height);
	while (i <= ms->height)
		ms->z[i++] = ft_calloc(sizeof(int), ms->width * ms->height);
	i = 0;
	while (i < ms->height)
	{
		j = 0;
		while (j < ms->width)
		{
			ms->z[i][j] = ft_atoi(ms->map[k++]);
			j++;
		}
		i++;
	}
}
