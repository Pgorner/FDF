/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:48:52 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/15 14:53:04 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_values(t_s *ms)
{
	ms->color = 0xFFFFFFFF;
	ms->col = 0xFF000099;
	ms->offset = 10;
	ms->width = 0;
	ms->height = 0;
	ms->size = 1000;
	ms->ang = 0.4;
	ms->sx = (WIDTH / 2 - ((ms->width / 2) * ms->offset));
	ms->sy = (HEIGHT / 2 - ((ms->height / 2) * ms->offset));
}

int	start_mlx(t_s *ms)
{
	ms->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	ms->win = mlx_new_image(ms->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(ms->mlx, ms->win, 0, 0);
	draw(ms);
	mlx_loop_hook(ms->mlx, key_input, ms);
	mlx_loop(ms->mlx);
	mlx_terminate(ms->mlx);
	safe_exit(ms);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_s		*ms;
	int		i;
	int		fd;

	i = argc;
	if (argc != 2)
		return (666);
	ms = malloc(sizeof(t_s));
	fd = open(argv[1], O_RDONLY);
	set_values(ms);
	get_input(ms, fd);
	start_mlx(ms);
	return (0);
}
