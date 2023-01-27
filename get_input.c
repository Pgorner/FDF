/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:36:36 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/25 14:22:14 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	z(t_s *ms)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	ms->z = ft_calloc(sizeof(int), ms->width*ms->height);
	while (i <= ms->height)
		ms->z[i++] = ft_calloc(sizeof(int), ms->width*ms->height);
	i = 0;
	while (i < ms->height)
	{
		j = 0;
		while (j < ms->width)
		{
			ms->z[i][j] = ft_atoi(ms->map[k++]);
			//printf("%s\n", ms->map[k]);
/* 			printf("i %i\n", i);
			printf("ft_atoi(ms->map[k]):%s\n", ms->map[k]); */
			j++;
		}

		i++;
	}
}

void	x(t_s *ms)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	ms->x = ft_calloc(sizeof(int), ms->width*ms->height);
	while (i <= ms->height)
		ms->x[i++] = ft_calloc(sizeof(int), ms->width + 1);
	i = 0;
	while (i < ms->height)
	{
		j = 0;
		while (j < ms->width)
		{
			if (j == 0)
				ms->x[i][j] = ms->sX;
			else
				ms->x[i][j] += ms->sX + (ms->offset * j);
			++j;
		}
		++i;
	}
}

void	y(t_s *ms)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	ms->y = ft_calloc(sizeof(int), ms->width*ms->height);
	while (i <= ms->height)
		ms->y[i++] = ft_calloc(sizeof(int), ms->width);
	i = 0;
	while (i < ms->height)
	{
		j = 0;
		while (j < ms->width)
		{
			ms->y[i][j] = ms->sY + (ms->offset * i);
			++j;
		}
		++i;
	}
}

int	countword(char const *s, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	i = -1;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (free(s1), str);
}

void	get_input(t_s *ms, int fd)
{
	char	*i;
	int		j;
	int		c;
	char	*tmp;
	char	*val;

	j = 0;
	c = 0;
	ms->line = get_next_line(fd);
	i = ms->line;
	val = malloc(sizeof(int)*ms->size);
	while (i)
	{
		tmp = ft_strtrim(ms->line, "\n");
		printf("%s", tmp);
		free(ms->line);
		val = ft_strjoin2(val, " ");
		c++;
		val = ft_strjoin2(val, tmp);
		ms->width = countword(tmp, ' ');
		free(tmp);
		ms->line = get_next_line(fd);
		i = ms->line;
		ms->height++;
	}
	val = ft_strjoin2(val, " ");
	ms->map = ft_split(val, ' ');
		printf("%s\n", ms->map[207]);
		printf("%s\n", ms->map[208]);
	ms->sX = (WIDTH/2 - ((ms->width/2)* ms->offset));
	ms->sY = (HEIGHT/2 - ((ms->height/2)* ms->offset));
	z(ms);
	x(ms);
	y(ms);
/* 	close(fd); */
}
/* void	get_input(t_s *ms, int fd)
{
	char	*i;

	int		j;
	int		c;
	char	**z;
	char	*tmp;

	j = 0;
	c = 0;
	ms->line = get_next_line(fd);
	i = ms->line;
	z = ft_calloc(sizeof(int), (unsigned long)CHAR_MAX);
	free(z);
	ms->z = ft_calloc(sizeof(int), ms->size);
	while (c <= ms->size)
		ms->z[c++] = ft_calloc(sizeof(int), ms->size);
	while (i)
	{
		tmp = ft_strtrim(ms->line, "\n");
		free(ms->line);
		z = ft_split(tmp, ' ');
		free(tmp);
		c = 0;
		printf("j%i\n", j);
		while (z[c] != NULL)
		{
			ms->z[j][c] = ft_atoi(z[c]); // LEAK LEAK LEAK LEAK
			free(z[c]);
			if (j == 0  && (ft_strchr(z[c], '\n') == 0))
				ms->width++;
			c++;
		}
		j++;
		free(z);
		ms->line = get_next_line(fd);
		i = ms->line;
		ms->height++;
	}
	c = 0;
	while (test[c])
	{
		free(test[c]);
		c++;
	}
	free(test);
	ms->sX = (WIDTH/2 - ((ms->width/2)* ms->offset));
	ms->sY = (HEIGHT/2 - ((ms->height/2)* ms->offset));
	x(ms);
	y(ms);
	close(fd);
}
 */
