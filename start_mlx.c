/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:17:15 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/15 16:19:01 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_s *ms, int i, int j)
{
	int		pixels;
	double	deltax;
	double	deltay;
	double	pixelx;
	double	pixely;

	if (ms->z[j][i] != 0 || ms->z[j][i + 1] != 0)
		ms->color = ms->col;
	deltax = ms->ex - ms->bx;
	deltay = ms->ey - ms->by;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = ms->bx;
	pixely = ms->by;
	while (pixels)
	{
		if ((pixelx > 1 && pixelx < WIDTH - 1)
			&& (pixely > 1 && pixely < HEIGHT - 1))
			mlx_put_pixel(ms->win, pixelx, pixely, ms->color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
	ms->color = 0xFFFFFFFF;
}

void	values(t_s *ms, int i, int j, int c)
{
	if (c == 1)
	{
		ms->bx = (ms->x[j][i] * cos(ms->ang)) - (ms->y[j][i]
				* cos(ms->ang));
		ms->by = (ms->x[j][i] * sin(ms->ang)) + (ms->y[j][i]
				* sin(ms->ang)) - ms->z[j][i];
		ms->ex = (ms->x[j][i + 1] * cos(ms->ang)) - (ms->y[j][i + 1]
				* cos(ms->ang));
		ms->ey = (ms->x[j][i + 1] * sin(ms->ang)) + (ms->y[j][i + 1]
				* sin(ms->ang)) - ms->z[j][i + 1];
	}
	else
	{
		ms->bx = (ms->x[j][i] * cos(ms->ang)) - (ms->y[j][i]
				* cos(ms->ang));
		ms->by = (ms->x[j][i] * sin(ms->ang)) + (ms->y[j][i]
				* sin(ms->ang)) - ms->z[j][i];
		ms->ex = (ms->x[j + 1][i] * cos(ms->ang)) - (ms->y[j + 1][i]
				* cos(ms->ang));
		ms->ey = (ms->x[j + 1][i] * sin(ms->ang)) + (ms->y[j + 1][i]
				* sin(ms->ang)) - ms->z[j + 1][i];
	}
}

void	draw(t_s *ms)
{
	int	i;
	int	j;

	j = -1;
	while (++j < ms->height)
	{
		i = -1;
		while (++i < ms->width)
		{
			values(ms, i, j, 1);
			if (i < ms->width - 1)
				draw_line(ms, i, j);
			values(ms, i, j, 0);
			if (j < ms->height - 1)
				draw_line(ms, i, j);
		}
	}
}

void	key_input(void *tmp)
{
	t_s	*ms;

	ms = (t_s *)tmp;
	if (mlx_is_key_down(ms->mlx, MLX_KEY_ESCAPE))
		safe_exit(ms);
}
