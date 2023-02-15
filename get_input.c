/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:36:36 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/15 14:48:56 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	char	*tmp;
	char	*val;

	ms->line = get_next_line(fd);
	i = ms->line;
	val = malloc(sizeof(int) * ms->size);
	while (i)
	{
		tmp = ft_strtrim(ms->line, "\n");
		free(ms->line);
		val = ft_strjoin2(val, " ");
		val = ft_strjoin2(val, tmp);
		ms->width = countword(tmp, ' ');
		free(tmp);
		ms->line = get_next_line(fd);
		i = ms->line;
		ms->height++;
	}
	val = ft_strjoin2(val, " ");
	ms->map = ft_split(val, ' ');
	free(val);
	x(ms);
	y(ms);
	z(ms);
}
