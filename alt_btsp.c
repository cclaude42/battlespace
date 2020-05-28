/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_btsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 19:51:57 by cclaude           #+#    #+#             */
/*   Updated: 2020/05/28 12:02:35 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btsp.h"

// DEBUGGING

void	print_map(char map[10][10])
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
			printf("%c", map[i][j++]);
		printf("\n");
		i++;
	}
	printf("\n");
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
			printf("%2.2d ", pdf[i][j++]);
		printf("\n");
		i++;
	}
	printf("\n");
}

// TOOLS

int		ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
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
	if (ft_strcmp(in, "BLOCKED") == 0)
		return (BLOCKED);
	else if (ft_strcmp(in, "SUNK") == 0)
		return (SUNK);
	else if (ft_strcmp(in, "HIT") == 0)
		return (HIT);
	else
		return (MISS);
}

void	clear_blocked(char (*map)[10][10], int (*pdf)[10][10], int i, int j)
{
	int	x;
	int	y;

	(*map)[i][j] = 'x';
	(*pdf)[i][j] = 0;
	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			if ((*map)[x][y] == 'b')
			{
				// print_map(*map);
				if (shoot(x, y) == BLOCKED)
					return ;
				(*map)[x][y] = 'x';
				(*pdf)[x][y] = 0;
			}
			y++;
		}
		x++;
	}
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

int		compute_coeff(char map[10][10], int i, int j)
{
	int		n;
	char	c;

	if ((c = map[i][j]) == 'b')
		map[i][j] = '.';
	n = 9 - ft_abs((float)i - 4.5) - ft_abs((float)j - 4.5);
	if (j > 0 && map[i][j - 1] == '.')
		n += 12;
	if (j < 9 && map[i][j + 1] == '.')
		n += 12;
	if (i > 0 && map[i - 1][j] == '.')
		n += 12;
	if (i < 9 && map[i + 1][j] == '.')
		n += 12;
	if (i > 0 && j > 0 && map[i - 1][j - 1] == '.')
		n += 8;
	if (i > 0 && j < 9 && map[i - 1][j + 1] == '.')
		n += 8;
	if (i < 9 && j > 0 && map[i + 1][j - 1] == '.')
		n += 8;
	if (i < 9 && j < 9 && map[i + 1][j + 1] == '.')
		n += 8;
	map[i][j] = c;
	return (n);
}

void	map_coeff(char map[10][10], int (*pdf)[10][10])
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
		clear_blocked(map, pdf, i, j);
	else if (hit == HIT)
	{
		(*map)[i][j] = 'x';
		(*pdf)[i][j] = 0;
	}
	else
	{
		(*map)[i][j] = ' ';
		(*pdf)[i][j] = 0;
	}
}

// MAIN

int		main(void)
{
	char	map[10][10];
	int		pdf[10][10];
	int		i;
	int		j;

	fill_map(&map);
	while (1)
	{
		map_coeff(map, &pdf);
		// print_map(map);
		// print_pdf(pdf);
		find_target(map, pdf, &i, &j);
		if (i == 10 || j == 10)
			return (0);
		react(&map, &pdf, 10 * i + j, shoot(i, j));
	}
	return (0);
}
