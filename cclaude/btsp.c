/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 19:51:57 by cclaude           #+#    #+#             */
/*   Updated: 2020/05/27 13:18:07 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btsp.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

int	ft_strcmp(const char *s1, const char *s2)
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

int	main(void)
{
	// Pas interdit !!!!!!
	char	map[10][10];
	int		pdf[10][10];
	char	in[10];
	char	out[4];
	int		i;
	int		j;
	int		idx;
	int		max;

	// MAP FILL (ONE TIME!)

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
			map[i][j++] = '.';
		i++;
	}

	int w;
	for (w = 0 ; w < 200 ; w++ ) {
	// LOOP : Assign coeff, find target, kill target
	i = 0;
	max = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			// printf("%c", map[i][j]);
			pdf[i][j] = 9 - ft_abs((float)i - 4.5) - ft_abs((float)j - 4.5);
			if (map[i][j] != 'x' && j > 0 && map[i][j - 1] != 'x')
				pdf[i][j] += 12;
			if (map[i][j] != 'x' && j < 9 && map[i][j + 1] != 'x')
				pdf[i][j] += 12;
			if (map[i][j] != 'x' && i > 0 && map[i - 1][j] != 'x')
				pdf[i][j] += 12;
			if (map[i][j] != 'x' && i < 9 && map[i + 1][j] != 'x')
				pdf[i][j] += 12;
			if (map[i][j] != 'x' && i > 0 && j > 0 && map[i - 1][j - 1] != 'x')
				pdf[i][j] += 8;
			if (map[i][j] != 'x' && i > 0 && j < 9 && map[i - 1][j + 1] != 'x')
				pdf[i][j] += 8;
			if (map[i][j] != 'x' && i < 9 && j > 0 && map[i + 1][j - 1] != 'x')
				pdf[i][j] += 8;
			if (map[i][j] != 'x' && i < 9 && j < 9 && map[i + 1][j + 1] != 'x')
				pdf[i][j] += 8;
			if (pdf[i][j] > max && map[i][j] == '.')
				max = pdf[i][j];
			j++;
		}
		i++;
	}

	// PRINT RESULTS

	// i = 0;
	// while (i < 10)
	// {
	// 	j = 0;
	// 	while (j < 10)
	// 		printf("%2.2d ", pdf[i][j++]);
	// 	printf("\n");
	// 	i++;
	// }
	// printf("\n");
	//
	// i = 0;
	// while (i < 10)
	// {
	// 	j = 0;
	// 	while (j < 10)
	// 		printf("%c", map[i][j++]);
	// 	printf("\n");
	// 	i++;
	// }
	// printf("\n");

	// (find target)
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (pdf[i][j] == max && map[i][j] == '.')
				break;
			j++;
		}
		if (j < 10 && pdf[i][j] == max && map[i][j] == '.')
			break;
		i++;
	}
	if (i == 10 || j == 10)
		return (0);

	// (kill target)
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
		map[i][j] = 'b';
	else if (ft_strcmp(in, "SUNK") == 0)
	{
		map[i][j] = 'x';
		pdf[i][j] = 0;
		i = 0;
		while (i < 10)
		{
			j = 0;
			while (j < 10)
			{
				if (map[i][j] == 'b')
					map[i][j] = '.';
				j++;
			}
			i++;
		}
	}
	else
	{
		map[i][j] = 'x';
		pdf[i][j] = 0;
	}

	}















	// FIRST LOOP ! BASE MAP

	// out[2] = '\n';
	// out[3] = '\0';
	// i = 0;
	// while (i < 10)
	// {
	// 	j = 0;
	// 	out[0] = 65 + i;
	// 	while (j < 10)
	// 	{
	// 		out[1] = 48 + j;
	// 		write(1, &out, 3);
	// 		read(0, &in, 10);
	// 		if (ft_strcmp(in, "BLOCKED\n") == 0)
	// 			map[i][j] = '.';
	// 		else
	// 			map[i][j] = 'x';
	// 		j++;
	// 	}
	// 	i++;
	// }


	// SECOND LOOP ! AFTER SHIELD

	// i = 0;
	// while (i < 10)
	// {
	// 	j = 0;
	// 	out[0] = 65 + i;
	// 	while (j < 10)
	// 	{
	// 		out[1] = 48 + j;
	// 		if (map[i][j] == '.')
	// 		{
	// 			write(1, &out, 0);
	// 			read(0, &in, 10);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	return (0);
}
