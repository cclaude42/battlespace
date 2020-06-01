/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sink.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 20:20:52 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/01 20:22:59 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btsp.h"

int		sink_spot(char (*map)[10][10], int i, int j)
{
	int	ret;

	if (i < 0 || i > 9 || j < 0 || j > 9 || (*map)[i][j] != '.')
		return (MISS);
	ret = shoot(i, j);
	if (ret == SUNK)
		mark_sunk(map, i, j);
	else if (ret == HIT)
	{
		if (sink_boat(map, i, j) == SUNK)
			return (SUNK);
	}
	else if (ret == BLOCKED)
		(*map)[i][j] = 'b';
	else if (ret == MISS)
		(*map)[i][j] = ' ';
	return (ret);
}

int		sink_plus(char (*map)[10][10], int i, int j)
{
	(*map)[i][j] = 'x';
	if (check_spot("box", map, i, j + 1) && sink_spot(map, i, j - 1) > HIT)
		return (1);
	if (check_spot("box", map, i, j - 1) && sink_spot(map, i, j + 1) > HIT)
		return (1);
	if (check_spot("box", map, i + 1, j) && sink_spot(map, i - 1, j) > HIT)
		return (1);
	if (check_spot("box", map, i - 1, j) && sink_spot(map, i + 1, j) > HIT)
		return (1);
	if (sink_spot(map, i, j - 1) > HIT)
		return (1);
	if (sink_spot(map, i, j + 1) > HIT)
		return (1);
	if (sink_spot(map, i - 1, j) > HIT)
		return (1);
	if (sink_spot(map, i + 1, j) > HIT)
		return (1);
	return (0);
}

int		sink_cross(char (*map)[10][10], int i, int j)
{
	(*map)[i][j] = 'x';
	if (check_spot("box", map, i - 1, j - 1)
		&& sink_spot(map, i + 1, j + 1) > HIT)
		return (1);
	if (check_spot("box", map, i + 1, j - 1)
		&& sink_spot(map, i - 1, j + 1) > HIT)
		return (1);
	if (check_spot("box", map, i - 1, j + 1)
		&& sink_spot(map, i + 1, j - 1) > HIT)
		return (1);
	if (check_spot("box", map, i + 1, j + 1)
		&& sink_spot(map, i - 1, j - 1) > HIT)
		return (1);
	if (sink_spot(map, i + 1, j + 1) > HIT)
		return (1);
	if (sink_spot(map, i - 1, j + 1) > HIT)
		return (1);
	if (sink_spot(map, i + 1, j - 1) > HIT)
		return (1);
	if (sink_spot(map, i - 1, j - 1) > HIT)
		return (1);
	return (0);
}

int		sink_boat(char (*map)[10][10], int i, int j)
{
	(*map)[i][j] = 'x';
	if (orientation(map) >= 0)
	{
		if (sink_plus(map, i, j))
			return (1);
		if (sink_cross(map, i, j))
			return (1);
	}
	else
	{
		if (sink_cross(map, i, j))
			return (1);
		if (sink_plus(map, i, j))
			return (1);
	}
	return (0);
}
