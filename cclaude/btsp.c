/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 19:51:57 by cclaude           #+#    #+#             */
/*   Updated: 2020/05/30 00:06:33 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btsp.h"

int		sink_boat(char (*map)[10][10], int (*pdf)[10][10], int i, int j);

char	map[10][10];

// DEBUGGING

void	print_map(char map[10][10], char *in, char *out)
{
	int	i;
	int	j;

	i = 0;
	fprintf(stderr, "\n%s\n%s\n", out, in);
	while (i < 10)
	{
		j = 0;
		while (j < 10)
			fprintf(stderr, "%c", map[i][j++]);
		fprintf(stderr, "\n");
		i++;
	}
	fprintf(stderr, "\n\n%s\n%s\n", out, in);
}

void	print_pdf(int pdf[10][10])
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
			fprintf(stderr, "%2.2d ", pdf[i][j++]);
		fprintf(stderr, "\n");
		i++;
	}
	fprintf(stderr, "\n");
}

// TOOLS

int		ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// FUNCTIONS

int		shoot(int i, int j)
{
	int		idx;
	char	in[10];
	char	out[4];

	out[0] = 65 + i;
	out[1] = 48 + j;
	out[2] = '\n';
	out[3] = '\0';
	write(1, &out, 3);
	read(0, &in, 10);
	idx = 0;
	while (in[idx] != '\n')
		idx++;
	in[idx] = '\0';
	// print_map(map, in, out);
	if (ft_strcmp(in, "BLOCKED") == 0)
		return (BLOCKED);
	else if (ft_strcmp(in, "SUNK") == 0)
		return (SUNK);
	else if (ft_strcmp(in, "HIT") == 0)
		return (HIT);
	else
		return (MISS);
}

int		check_spot(char *marks, char (*map)[10][10], int i, int j)
{
	if (i < 0 || i > 9 || j < 0 || j > 9)
		return (0);
	else
		return (ft_strchr(marks, (*map)[i][j]));
}

void	clear_sides(char (*map)[10][10], int i, int j)
{
	if (check_spot(".", map, i, j - 1))
		(*map)[i][j - 1] = ' ';
	if (check_spot(".", map, i, j + 1))
		(*map)[i][j + 1] = ' ';
	if (check_spot(".", map, i - 1, j))
		(*map)[i - 1][j] = ' ';
	if (check_spot(".", map, i + 1, j))
		(*map)[i + 1][j] = ' ';
	if (check_spot(".", map, i - 1, j - 1))
		(*map)[i - 1][j - 1] = ' ';
	if (check_spot(".", map, i - 1, j + 1))
		(*map)[i - 1][j + 1] = ' ';
	if (check_spot(".", map, i + 1, j - 1))
		(*map)[i + 1][j - 1] = ' ';
	if (check_spot(".", map, i + 1, j + 1))
		(*map)[i + 1][j + 1] = ' ';
}

void	mark_sunk(char (*map)[10][10], int (*pdf)[10][10], int i, int j)
{
	(*map)[i][j] = 'o';
	(*pdf)[i][j] = 0;
	if (check_spot("x", map, i, j - 1))
		mark_sunk(map, pdf, i, j - 1);
	if (check_spot("x", map, i, j + 1))
		mark_sunk(map, pdf, i, j + 1);
	if (check_spot("x", map, i - 1, j))
		mark_sunk(map, pdf, i - 1, j);
	if (check_spot("x", map, i + 1, j))
		mark_sunk(map, pdf, i + 1, j);
	if (check_spot("x", map, i - 1, j - 1))
		mark_sunk(map, pdf, i - 1, j - 1);
	if (check_spot("x", map, i - 1, j + 1))
		mark_sunk(map, pdf, i - 1, j + 1);
	if (check_spot("x", map, i + 1, j - 1))
		mark_sunk(map, pdf, i + 1, j - 1);
	if (check_spot("x", map, i + 1, j + 1))
		mark_sunk(map, pdf, i + 1, j + 1);
	clear_sides(map, i, j);
}

void	clear_blocked(char (*map)[10][10], int (*pdf)[10][10])
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if ((*map)[i][j] == 'b')
			{
				ret = shoot(i, j);
				if (ret == BLOCKED)
					return ;
				(*map)[i][j] = 'x';
				(*pdf)[i][j] = 0;
				if (ret == SUNK)
					mark_sunk(map, pdf, i, j);
			}
			j++;
		}
		i++;
	}
}

int		got_shield(char (*map)[10][10], int (*pdf)[10][10], int i, int j)
{
	if (check_spot("x", map, i, j - 1))
		return (0);
	if (check_spot("x", map, i, j + 1))
		return (0);
	if (check_spot("x", map, i - 1, j))
		return (0);
	if (check_spot("x", map, i + 1, j))
		return (0);
	if (check_spot("x", map, i - 1, j - 1))
		return (0);
	if (check_spot("x", map, i - 1, j + 1))
		return (0);
	if (check_spot("x", map, i + 1, j - 1))
		return (0);
	if (check_spot("x", map, i + 1, j + 1))
		return (0);
	(*map)[i][j] = ' ';
	(*pdf)[i][j] = 0;
	return (1);
}

int		orientation_spot(char (*map)[10][10], int i, int j)
{
	int	or;

	or = 0;
	if (check_spot("box", map, i, j - 1))
		or++;
	if (check_spot("box", map, i, j + 1))
		or++;
	if (check_spot("box", map, i - 1, j))
		or++;
	if (check_spot("box", map, i + 1, j))
		or++;
	if (check_spot("box", map, i - 1, j - 1))
		or--;
	if (check_spot("box", map, i - 1, j + 1))
		or--;
	if (check_spot("box", map, i + 1, j - 1))
		or--;
	if (check_spot("box", map, i + 1, j + 1))
		or--;
	return (or);
}

int		orientation(char (*map)[10][10])
{
	int	i;
	int	j;
	int	or;

	or = 0;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (check_spot("box", map, i, j))
				or += orientation_spot(map, i, j);
			j++;
		}
		i++;
	}
	return (or);
}

int		sink_spot(char (*map)[10][10], int (*pdf)[10][10], int i, int j)
{
	int	ret;

	if (i < 0 || i > 9 || j < 0 || j > 9 || (*map)[i][j] != '.')
		return (MISS);
	ret = shoot(i, j);
	if (ret == SUNK)
		mark_sunk(map, pdf, i, j);
	else if (ret == HIT)
		sink_boat(map, pdf, i, j);
	else if (ret == BLOCKED)
	{
		(*map)[i][j] = 'b';
		(*pdf)[i][j] = 0;
	}
	else if (ret == MISS)
	{
		(*map)[i][j] = ' ';
		(*pdf)[i][j] = 0;
	}
	return (ret);
}

int		sink_plus(char (*map)[10][10], int (*pdf)[10][10], int i, int j)
{
	if (check_spot("box", map, i, j + 1) && sink_spot(map, pdf, i, j - 1) > HIT)
		return (1);
	if (check_spot("box", map, i, j - 1) && sink_spot(map, pdf, i, j + 1) > HIT)
		return (1);
	if (check_spot("box", map, i + 1, j) && sink_spot(map, pdf, i - 1, j) > HIT)
		return (1);
	if (check_spot("box", map, i - 1, j) && sink_spot(map, pdf, i + 1, j) > HIT)
		return (1);
	if (sink_spot(map, pdf, i, j - 1) > HIT)
		return (1);
	if (sink_spot(map, pdf, i, j + 1) > HIT)
		return (1);
	if (sink_spot(map, pdf, i - 1, j) > HIT)
		return (1);
	if (sink_spot(map, pdf, i + 1, j) > HIT)
		return (1);
	return (0);
}

int		sink_cross(char (*map)[10][10], int (*pdf)[10][10], int i, int j)
{
	if (check_spot("box", map, i - 1, j - 1)
		&& sink_spot(map, pdf, i + 1, j + 1) > HIT)
		return (1);
	if (check_spot("box", map, i + 1, j - 1)
		&& sink_spot(map, pdf, i - 1, j + 1) > HIT)
		return (1);
	if (check_spot("box", map, i - 1, j + 1)
		&& sink_spot(map, pdf, i + 1, j - 1) > HIT)
		return (1);
	if (check_spot("box", map, i + 1, j + 1)
		&& sink_spot(map, pdf, i - 1, j - 1) > HIT)
		return (1);
	if (sink_spot(map, pdf, i + 1, j + 1) > HIT)
		return (1);
	if (sink_spot(map, pdf, i - 1, j + 1) > HIT)
		return (1);
	if (sink_spot(map, pdf, i + 1, j - 1) > HIT)
		return (1);
	if (sink_spot(map, pdf, i - 1, j - 1) > HIT)
		return (1);
	return (0);
}

int		sink_boat(char (*map)[10][10], int (*pdf)[10][10], int i, int j)
{
	(*map)[i][j] = 'x';
	(*pdf)[i][j] = 0;
	if (orientation(map) >= 0)
	{
		if (sink_plus(map, pdf, i, j))
			return (1);
		if (sink_cross(map, pdf, i, j))
			return (1);
	}
	else
	{
		if (sink_cross(map, pdf, i, j))
			return (1);
		if (sink_plus(map, pdf, i, j))
			return (1);
	}
	return (0);
}

int		find_max(char map[10][10], int pdf[10][10])
{
	int	max;
	int	i;
	int	j;

	max = 0;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (pdf[i][j] > max && map[i][j] == '.')
				max = pdf[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

void	find_target(char map[10][10], int pdf[10][10], int *i, int *j)
{
	int	max;

	max = find_max(map, pdf);
	*i = 0;
	while (*i < 10)
	{
		*j = 0;
		while (*j < 10)
		{
			if (pdf[*i][*j] == max && map[*i][*j] == '.')
				break ;
			(*j)++;
		}
		if (*j < 10 && pdf[*i][*j] == max && map[*i][*j] == '.')
			break ;
		(*i)++;
	}
}

void	fill_map(char (*map)[10][10])
{
	int		i;
	int		j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
			(*map)[i][j++] = '.';
		i++;
	}
}

int		compute_coeff(char (*map)[10][10], int i, int j)
{
	int	n;

	if (check_spot("b.", map, i, j) == 0)
		return (0);
	n = 9 - ft_abs((float)i - 4.5) - ft_abs((float)j - 4.5);
	if (check_spot("b.", map, i, j - 1))
		n += 12;
	if (check_spot("b.", map, i, j + 1))
		n += 12;
	if (check_spot("b.", map, i - 1, j))
		n += 12;
	if (check_spot("b.", map, i + 1, j))
		n += 12;
	if (check_spot("b.", map, i - 1, j - 1))
		n += 8;
	if (check_spot("b.", map, i - 1, j + 1))
		n += 8;
	if (check_spot("b.", map, i + 1, j - 1))
		n += 8;
	if (check_spot("b.", map, i + 1, j + 1))
		n += 8;
	return (n);
}

void	map_coeff(char (*map)[10][10], int (*pdf)[10][10])
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			(*pdf)[i][j] = compute_coeff(map, i, j);
			j++;
		}
		i++;
	}
}

void	react(char (*map)[10][10], int (*pdf)[10][10], int ij, int hit)
{
	int	i;
	int	j;

	i = ij / 10;
	j = ij % 10;
	if (hit == BLOCKED)
		(*map)[i][j] = 'b';
	else if (hit == SUNK)
	{
		if (got_shield(map, pdf, i, j))
			clear_blocked(map, pdf);
		else
			mark_sunk(map, pdf, i, j);
	}
	else if (hit == HIT)
		sink_boat(map, pdf, i, j);
	else
	{
		(*map)[i][j] = ' ';
		(*pdf)[i][j] = 0;
	}
}

// MAIN

int		main(void)
{
	int		pdf[10][10];
	int		i;
	int		j;

	fill_map(&map);
	while (1)
	{
		map_coeff(&map, &pdf);
		find_target(map, pdf, &i, &j);
		if (i == 10 || j == 10)
			return (0);
		react(&map, &pdf, 10 * i + j, shoot(i, j));
	}
	return (0);
}
